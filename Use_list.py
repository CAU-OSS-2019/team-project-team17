from selenium import webdriver
from bs4 import BeautifulSoup
import time

User_list_win = []

driver =webdriver.Chrome(r"C:\Users\yoons\Desktop/chromedriver.exe")
driver.implicitly_wait(3)
driver.get('https://www.op.gg/')



search_name = driver.find_element_by_name('userName')
search_name.send_keys('Gen G Bonnie') # 여기다가 사용자 이름 넣어주기
search_name.submit()

html = driver.page_source 
soup = BeautifulSoup(html, 'html.parser')

num_won=0
num_lost=0
need=5
for user in [1]:
    duo_prev=0
    while True :
        driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[2]/div[4]/a').click()#더보기클릭
        game_prev=0
        duo=soup.select('#SummonerLayoutContent > div.tabItem.Content.SummonerLayoutContent.summonerLayout-summary > div.SideContent > div.SummonersMostGame.Box > div.Content > table > tbody > tr:nth-child(1) > td.SummonerName.Cell > a')
        duo_name=duo[0].text#SANDBOX
        gamelist=soup.find('div',"GameItemList")
        games=soup.select('.GameItemWrap:contains("'+duo_name+'")')
        game_next=len(games)
        print(game_next, '1')

        while game_prev < game_next : # 더보기 증가하면 계속 클릭
            game_prev=game_next
            driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[2]/div['+str(need)+']/a').click()#더보기클릭
            need+=1
            html = driver.page_source 
            soup = BeautifulSoup(html, 'html.parser')
            gamelist=soup.find('div',"GameItemList")
            games=soup.select('.GameItemWrap:contains("'+duo_name+'")')
            game_next=(len(games))
            print(game_next, '2')
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
        break
                