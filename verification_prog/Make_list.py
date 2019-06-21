from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions
from selenium.webdriver.common.by import By
from selenium.common.exceptions import ElementNotVisibleException
from selenium.webdriver.common.keys import Keys
from bs4 import BeautifulSoup
from random import *
import time 
import os


Check = False
Num = 0
Count = 0
Done = False
User_name = '뚱땡이버거' # 처음 검색할 사용자
Next_user = ''
User_list = []
Check_list = []
Duo_list = []

def List_Append():
    time.sleep(3)
    
    global Check
    global Count
    global User_name
    global Next_user
    global Num
    global Done

    Check_list.append(User_name)

    html = driver.page_source
    soup = BeautifulSoup(html, 'html.parser')

    duo_info_name = soup.select('div > table > tbody > tr > td.SummonerName.Cell')
    duo_info_count = soup.select('div > table > tbody > tr > td.GameCount.Cell')

    for n in duo_info_count:
        if int(n.text.strip()) >= 5: 
            Check = True

    if Check == True:
        driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[1]/div/ul/li[2]/a').click()
        time.sleep(3)

        html = driver.page_source
        soup = BeautifulSoup(html, 'html.parser')
        Search_user = soup.select('div.SummonerName')
        
        Random_num = randint(0, len(Search_user) - 1)
        Next_user = Search_user[Random_num].text.strip()
        while (Next_user == User_name) or Next_user in Check_list:
            Random_num = randint(0, len(Search_user) - 1)
            Next_user = Search_user[Random_num].text.strip()
        
        for i in duo_info_name:
            for j in Search_user:
                if  j.text.strip() == i.text.strip(): 
                    Count += 1
            
            if Count >= 5:
                Duo_list.append(i.text.strip())

            Count = 0
    else:
        driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[1]/div/ul/li[2]/a').click()
        time.sleep(3)

        html = driver.page_source
        soup = BeautifulSoup(html, 'html.parser')
        Search_user = soup.select('div.SummonerName')

        if soup.select('div.Message')[0].text.strip() != "기록된 전적이 없습니다.":
            Done = True
            return 0
        
        Random_num = randint(1, 10)
        Next_user = Search_user[Random_num].text.strip()

        while Next_user == User_name:
            Random_num = randint(1, 10)
            Next_user = Search_user[Random_num].text.strip()

    if Duo_list:
        Num += 1
        User_list.append(User_name)

    User_name = Next_user
    Check = False
    Duo_list.clear()
    
    search_name2 = driver.find_element_by_name('userName')
    search_name2.send_keys(Next_user)
    search_name2.send_keys(Keys.RETURN)

driver = webdriver.Chrome(executable_path=os.path.abspath("chromedriver.exe"))
driver.implicitly_wait(3)
driver.get('https://www.op.gg/')
search_name = driver.find_element_by_name('userName')
search_name.send_keys(User_name)
search_name.submit()

Check_list.append(User_name)

html = driver.page_source
soup = BeautifulSoup(html, 'html.parser')

duo_info_name = soup.select('div > table > tbody > tr > td.SummonerName.Cell')
duo_info_count = soup.select('div > table > tbody > tr > td.GameCount.Cell')

for n in duo_info_count:
    if int(n.text.strip()) >= 5: 
        Check = True

if Check == True:
    driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[1]/div/ul/li[2]/a').click()
    time.sleep(3)

    html = driver.page_source
    soup = BeautifulSoup(html, 'html.parser')
    Search_user = soup.select('div.SummonerName')
    
    Random_num = randint(1, len(Search_user))
    Next_user = Search_user[Random_num].text.strip()
    while Next_user == User_name:
        Random_num = randint(1, len(Search_user))
        Next_user = Search_user[Random_num].text.strip()

    for i in duo_info_name:
        for j in Search_user:
            if  j.text.strip() == i.text.strip(): 
                Count += 1
        
        if Count >= 5:
            Duo_list.append(i.text.strip())

        Count = 0
else:
    driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[1]/div/ul/li[2]/a').click()
    time.sleep(3)

    html = driver.page_source
    soup = BeautifulSoup(html, 'html.parser')
    Search_user = soup.select('div.SummonerName')
    
    Random_num = randint(0, len(Search_user) - 1)
    Next_user = Search_user[Random_num].text.strip()
    while Next_user == User_name:
        Random_num = randint(0, len(Search_user) - 1)
        Next_user = Search_user[Random_num].text.strip()

if Duo_list:
    Num += 1
    User_list.append(User_name)

User_name = Next_user
Check = False
Duo_list.clear()

search_name2 = driver.find_element_by_name('userName')
search_name2.send_keys(Next_user) # 사용자 이름
search_name2.send_keys(Keys.RETURN)

while Num != 1: #  구하고 싶은 유저의 수 입력
    List_Append()
    if Done == True:
        break

print(User_list)

F = open("DuoList.txt", 'a')
F.write('\n'.join(User_list))
F.close()
#여기까지 목록만든거

num_won=0
num_lost=0

for user in User_list:
    need=5 #중요
    driver.get('https://www.op.gg/')

    search_name = driver.find_element_by_name('userName')
    search_name.send_keys(user) # 여기다가 사용자 이름 넣어주기
    search_name.submit()

    html = driver.page_source 
    soup = BeautifulSoup(html, 'html.parser')
    
    duo_prev=0

    driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[1]/div/ul/li[2]/a').click()
    
    driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[2]/div[4]/a').click()#더보기클릭
    game_prev=0
    duo=soup.select('#SummonerLayoutContent > div.tabItem.Content.SummonerLayoutContent.summonerLayout-summary > div.SideContent > div.SummonersMostGame.Box > div.Content > table > tbody > tr:nth-child(1) > td.SummonerName.Cell > a')
    duo_name=duo[0].text# 검색하는 사람 듀오 닉넴!!!
    
    print(user,'가 ',duo_name,'랑 해서 얼마나 많이 이긴건지 크롤링중')
    gamelist=soup.find('div',"GameItemList")
    games=soup.select('.GameItemWrap:contains("'+duo_name+'")')
    game_next=len(games)
    print('게임 한 횟수' ,game_next)

    while game_prev < game_next : # 더보기 증가하면 계속 클릭
        game_prev=game_next
        driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[2]/div['+str(need)+']/a').click()#더보기클릭
        need+=1
        html = driver.page_source 
        soup = BeautifulSoup(html, 'html.parser')
        gamelist=soup.find('div',"GameItemList")
        games=soup.select('.GameItemWrap:contains("'+duo_name+'")')
        game_next=(len(games))
        print('게임 한 횟수' ,game_next)
        if need==10 : # 이거 안하면 무한루프임 더보기가 need-4 번 눌린다는 뜻 need-5일수도있음
            break
            
        
        
    for game in games: # 승리횟수 패배횟수 세기
        if game.find('div','GameResult').get_text().strip() == '승리':
            num_won+=1
        elif game.find('div','GameResult').get_text().strip() == '패배':
            num_lost+=1

    print('승 :',num_won)
    print('패 :',num_lost)
    percentage=num_won / (num_lost+num_won) *100
    print(percentage,'%')
        
                