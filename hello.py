from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from bs4 import BeautifulSoup
import time

driver = webdriver.Chrome(r"C:\\Users\\이민희\\Downloads\\chromedriver.exe") 
driver.implicitly_wait(3)
driver.get('https://www.op.gg/')

search_name = driver.find_element_by_name('userName')
search_name.send_keys('Hide on bush') # 여기다가 사용자 이름 넣어주기
search_name.submit()

#검색 메인화면
html = driver.page_source #페이지의 elements 모두 가져오기
soup = BeautifulSoup(html, 'lxml') #BeautifulSoup 사용하기
#BeautifulSoup 객체로 변환 -> 웹문서 파싱 상태 -> 태그 별로 분해되어 태그로 구성된 트리

UserTierRankInfo = soup.find('div', class_='TierRankInfo')
DivUserTierRankInfo = UserTierRankInfo.find_all('div')
print("TireRank : " + DivUserTierRankInfo[1].get_text())
print("LeaguePoints : " + DivUserTierRankInfo[2].find('span', class_='LeaguePoints').get_text().strip()[:-3])
print("wins : " + DivUserTierRankInfo[2].find('span', class_='wins').get_text()[:-1]) #승이라는 글씨 제거하고 숫자만
print("losses : " + DivUserTierRankInfo[2].find('span', class_='losses').get_text()[:-1])

UserPositionStatContent = soup.find_all('div', class_='PositionStatContent')
print("포지션1 : " + UserPositionStatContent[0].div.get_text())
UserPositionStatContentDetail0 = UserPositionStatContent[0].find_all('b')
print("RoleRate1 : " + UserPositionStatContentDetail0[0].get_text())
print("WinRatio1 : " + UserPositionStatContentDetail0[1].get_text())
print("포지션2 : " + UserPositionStatContent[1].div.get_text())
UserPositionStatContentDetail1 = UserPositionStatContent[1].find_all('b')
print("RoleRate2 : " + UserPositionStatContentDetail1[0].get_text())
print("WinRatio2 : " + UserPositionStatContentDetail1[1].get_text())

print()

a = driver.find_element_by_xpath('/html/body/div[1]/div[2]/div/div/div[3]/dl/dd[2]/a')
driver.get(a.get_attribute('href'))
driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[3]/div/div/div[2]/div[1]/div/div[1]/div/div[2]').click()
time.sleep(5)

html = driver.page_source
soup = BeautifulSoup(html, 'lxml')

UserChampionList = soup.find('tbody', class_='Body')
UserChampionListRows = UserChampionList.find_all('tr')

for UserChampionListRow in UserChampionListRows:
    print("ChampionName: " + UserChampionListRow.find(class_='ChampionName Cell').get_text().strip())
    try:  
        print("승: " + UserChampionListRow.find(class_='Text Left').get_text()[:-1])
    except AttributeError:
        print("승: 0")

    try:  
        print("패: " + UserChampionListRow.find(class_='Text Right').get_text()[:-1])
    except AttributeError:
        print("패: 0")

    print("Kill: " + UserChampionListRow.find(class_='Kill').get_text())
    print("Death: " + UserChampionListRow.find(class_='Death').get_text())
    print("Assist: " + UserChampionListRow.find(class_='Assist').get_text())


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