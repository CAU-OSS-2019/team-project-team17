from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from bs4 import BeautifulSoup
import time
import pymysql

host_name = 'gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com'
username = 'gamehaeduo'
password = 'caugamehaeduo'
database_name = 'gamehaeduo'

db = pymysql.connect(
    host= host_name,
    port=3306,
    user= username,
    passwd= password,
    db= database_name,
    charset='utf8')

cursor = db.cursor()

driver = webdriver.Chrome('/usr/bin/chromedriver',chrome_options=options)


sql = """
        TRUNCATE TABLE baseCharacterInfo
"""
cursor.execute(sql)

sql = """
        TRUNCATE TABLE bestPickCharacter
"""
cursor.execute(sql)


tireList = ['iron', 'bronze', 'silver', 'gold', '', 'diamond', 'master']

driver.get('https://www.leagueofgraphs.com/ko/champions/counters/garen')
driver.find_element_by_xpath('//*[@id="championsFilter"]/a').click()

html = driver.page_source
soup = BeautifulSoup(html, 'lxml')

for link in soup.select('#drop-champions> ul > li > a'):
    if 'href' in link.attrs:
        characterName = link.attrs['href'][23:]
    if characterName == '':
        continue
    for tire in tireList:
        driver.get('https://www.leagueofgraphs.com/ko/champions/builds/'+characterName+'/'+tire)
        html = driver.page_source
        soup = BeautifulSoup(html, 'lxml')

        base_win_rate = float(soup.find('div', id="graphDD2").get_text().strip()[:-1])

        sql = """
                INSERT IGNORE baseCharacterInfo
                    (character_name, rank, win_rate)
                VALUES
                    (%s, %s, %s)
        """
        
        cursor.execute(sql, (characterName, tire if (tire != '') else 'platinum', base_win_rate))

        driver.get('https://www.leagueofgraphs.com/ko/champions/counters/'+characterName+'/'+tire)
        driver.find_element_by_xpath('//*[@id="mainContent"]/div/div[1]/div/table/tbody//td/button').click()

        html = driver.page_source
        soup = BeautifulSoup(html, 'lxml')

        DataTable = soup.find('table', class_='data_table sortable_table')
        DataTableNames = DataTable.find_all('div', class_='txt')
        DataTableWinRatios = DataTable.select('#mainContent > div > div:nth-child(1) > div > table > tbody > tr > td:nth-child(2) > div.progress-bar-container.show-for-small-down-custom > span')

        for DataTableName, DataTableWinRatio in zip(DataTableNames,DataTableWinRatios):
            bestCharacterName = DataTableName.span.get_text()
            des = DataTableName.i.get_text()
            winRate = float(DataTableWinRatio.get_text()[1:-1])
            sql = """
                INSERT IGNORE INTO bestPickCharacter
                    (base_character_name, rank, best_character_name, win_rate, description)
                VALUES
                    (%s, %s, %s, %s, %s)
            """
            cursor.execute(sql, (characterName, tire if (tire != '') else 'platinum', bestCharacterName, winRate, des))

db.commit()

db.close()
