from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions
from selenium.webdriver.common.by import By
from selenium.common.exceptions import ElementNotVisibleException
from selenium.webdriver.common.keys import Keys
from bs4 import BeautifulSoup
from random import *
import time 


Check = False
Num = 0
Count = 0
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

driver = webdriver.Chrome(r'C:\Users\dbsks\AppData\Local\Programs\Python\Python37-32\chromedriver.exe')
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

while Num != 5: #  구하고 싶은 유저의 수 입력
    List_Append()

print(User_list)

F = open("DuoList.txt", 'a')
F.write('\n'.join(User_list))
F.close()