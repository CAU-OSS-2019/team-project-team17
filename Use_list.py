from selenium import webdriver
from bs4 import BeautifulSoup
import time
import Make_list

def use_list(User_list[]):
    User_list_win = []

    driver =webdriver.Chrome(r"C:\Users\yoons\Desktop/chromedriver.exe")
    driver.implicitly_wait(3)
    driver.get('https://www.op.gg/')



    search_name = driver.find_element_by_name('userName')
    search_name.send_keys('Gen G Bonnie') # 여기다가 사용자 이름 넣어주기
    search_name.submit()

    html = driver.page_source 
    soup = BeautifulSoup(html, 'html.parser')

    for user in Make_list.User_list:
        duo_prev=0
        while True :
            driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[2]/div[2]/div/div[2]/div[4]/a').click()#더보기클릭
            gamelist=soup.find('div',"GameItemList")
            duo=gamelist.find_all(user)
            if len(duo) > duo_prev :
                duo_prev = len(duo)
                #num_won=
                #num_lost=
                continue
            else : 
                User_list_win= num_won/(num_won+num_lost)*100
                break





