from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from bs4 import BeautifulSoup
import time
import pymysql

driver = webdriver.Chrome(r"C:\\Users\\이민희\\Downloads\\chromedriver.exe") 
driver.implicitly_wait(3)
driver.get('https://www.op.gg/') 

db = pymysql.connect(host='gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com', port=3306, user= 'gamehaeduo', passwd= 'caugamehaeduo', db='gamehaeduo', charset='utf8')
cursor = db.cursor()

search_name = driver.find_element_by_name('userName')
user_character_name = 'Hide on bush' # 여기다가 db에서 꺼낸 사용자 이름 넣어주기
search_name.send_keys(user_character_name) 
search_name.submit()

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

#sql = "INSERT INTO cpu_info (id, name, model_num, model_type) VALUES(" + "3" + ", 'i5', '7700', 'Kaby Lake')"
#insert update delete 등의 문장을 db 서버에 보냄

#cursor.execute(sql)

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

cursor.execute("SHOW TABLES")

db.commit() #데이터를 커밋

db.close()