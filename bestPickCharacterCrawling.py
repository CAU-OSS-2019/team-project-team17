from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from bs4 import BeautifulSoup
import time
import pymysql

db = pymysql.connect(host='gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com', port=3306, user= 'gamehaeduo', passwd= 'caugamehaeduo', db='gamehaeduo', charset='utf8')
cursor = db.cursor()

driver = webdriver.Chrome(r"C:\\Users\\이민희\\Downloads\\chromedriver.exe") 

characterNamesList = ['garen', 'galio', 'gangplank'] #디비에 있는 캐릭터 이름 다 넣어주기
tireList = ['iron', 'bronze', 'silver', 'gold', '', 'diamond', 'master']

for characterName in characterNamesList:
    for tire in tireList:
        driver.get('https://www.leagueofgraphs.com/ko/champions/counters/'+characterName+'/'+tire)
        driver.find_element_by_xpath('//*[@id="mainContent"]/div/div[1]/div/table/tbody//td/button').click()
        html = driver.page_source
        soup = BeautifulSoup(html, 'lxml')

        DataTable = soup.find('table', class_='data_table sortable_table')
        DataTableNames = DataTable.find_all('div', class_='txt')
        DataTableWinRatios = DataTable.select('#mainContent > div > div:nth-child(1) > div > table > tbody > tr > td:nth-child(2) > div.progress-bar-container.show-for-small-down-custom > span')

        for DataTableName, DataTableWinRatio in zip(DataTableNames,DataTableWinRatios):
            print("이름: "+ DataTableName.span.get_text())
            print("설명: "+ DataTableName.i.get_text())
            print("승률: "+ DataTableWinRatio.get_text()[1:-1])

cursor.execute("SHOW TABLES")

db.commit() #데이터를 커밋

db.close()