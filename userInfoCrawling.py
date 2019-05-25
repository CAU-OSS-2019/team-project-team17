# HOST와 PORT를 적어주세요!!!!!!



from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from bs4 import BeautifulSoup
import time
import pymysql
import socketserver
import threading

lock = threading.Lock() # mutual exclusion을 위한 뮤텍스

HOST = ''
PORT = 9009 #호스트와 포트는 소켓 서버를 위한 것

host_name = 'gamehaeduo-db.c8xdbny5rkis.ap-northeast-2.rds.amazonaws.com' # DB 주소 세팅
username = 'gamehaeduo'
password = 'caugamehaeduo'
database_name = 'gamehaeduo'

db = pymysql.connect( # DB 연결
    host= host_name,
    port=3306,
    user= username,
    passwd= password,
    db= database_name,
    charset='utf8')
cursor = db.cursor()

class UserManager:

    def __init__(self):
        self.users = {} #유저 리스트 초기화

    def addUser(self, nickname, conn, addr):#유저 리스트에 추가
        if nickname in self.users:
            conn.send('ERROR:01'.encode())
            return None
        lock.acquire()
        self.users[nickname] = (conn,addr)
        lock.release()

        print(nickname,'is Connected')






        print('connected client [%d]' %len(self.users))

    def removeUser(self, nickname):#유저 연결 해제
        if nickname not in self.users:
            return

        lock.acquire()
        del self.users[nickname]
        lock.release()

        print(nickname,'is Disconnected')

        print('connected client [%d]' %len(self.users))

    def messageHandler(self,nickname,msg):#클라이언트에게 전송받은 요청 처리

        if msg.strip() == '/quit':
            self.removeUser(nickname) #removeUser
            return -1

    def sendMessage(self,nickname,msg):
        conn,addr = self.users[nickname]
        conn.send(msg.encode())


    def crawlUser(user_nickname):
    
        driver = webdriver.Chrome(r"C:\\Users\\songsari\\Desktop\\chromedriver.exe") 
        driver.implicitly_wait(3)
        driver.get('https://www.op.gg/') 

        search_name = driver.find_element_by_name('userName')

        user_nick = user_nickname # 여기다가 db에서 꺼낸 사용자 이름 넣어주기
        #user_login_id = 'minhee0325' 아이디는 아마 필요없는 거 같아서 주석처리했씁니다

        search_name.send_keys(user_nick) 
        search_name.submit()

        html = driver.page_source
        soup = BeautifulSoup(html, 'lxml')

        UserTierRankInfo = soup.find('div', class_='TierRankInfo')

        DivUserTierRankInfo = UserTierRankInfo.find_all('div')
        TireRank= DivUserTierRankInfo[1].get_text()
        win = int(DivUserTierRankInfo[2].find('span', class_='wins').get_text()[:-1])
        loss = int(DivUserTierRankInfo[2].find('span', class_='losses').get_text()[:-1])

        try:
            sql = """
                INSERT INTO userEntireInfo
                    (nickname, rank, wins, losses)
                VALUES
                    (%s, %s, %s, %s)
                """
            cursor.execute(sql, (user_nick, TireRank, win, loss))
        except pymysql.IntegrityError:
            sql = """
                UPDATE userEntireInfo SET rank = %s, wins = %s, losses = %s WHERE nickname = %s
                """
            cursor.execute(sql, (TireRank, win, loss, user_nick))


        UserPositionStatContent = soup.find_all('div', class_='PositionStatContent')

        position1 = UserPositionStatContent[0].div.get_text()
        UserPositionStatContentDetail0 = UserPositionStatContent[0].find_all('b')
        RoleRate1 = float(UserPositionStatContentDetail0[0].get_text())
        WinRatio1 = float(UserPositionStatContentDetail0[1].get_text())

        position2 = UserPositionStatContent[1].div.get_text()
        UserPositionStatContentDetail1 = UserPositionStatContent[1].find_all('b')
        RoleRate2 = float(UserPositionStatContentDetail1[0].get_text())
        WinRatio2 = float(UserPositionStatContentDetail1[1].get_text())

        try:
            sql = """
                INSERT INTO userPosition
                    (nickname, position, role_rate, win_rate)
                values
                    (%s, %s, %s, %s)
                """
            cursor.execute(sql, (user_nick, position1, RoleRate1, WinRatio1))
            cursor.execute(sql, (user_nick, position2, RoleRate2, WinRatio2))
        except pymysql.IntegrityError:
            sql = """
                DELETE FROM userPosition
                WHERE nickname = %s
                """
            cursor.execute(sql, user_nick)

            sql = """
                INSERT INTO userPosition
                    (nickname, position, role_rate, win_rate)
                values
                    (%s, %s, %s, %s)
                """
        cursor.execute(sql, (user_nick, position1, RoleRate1, WinRatio1))
        cursor.execute(sql, (user_nick, position2, RoleRate2, WinRatio2))


        a = driver.find_element_by_xpath('/html/body/div[1]/div[2]/div/div/div[3]/dl/dd[2]/a')
        driver.get(a.get_attribute('href'))
        driver.find_element_by_xpath('//*[@id="SummonerLayoutContent"]/div[3]/div/div/div[2]/div[1]/div/div[1]/div/div[2]').click()
        time.sleep(5)

        html = driver.page_source
        soup = BeautifulSoup(html, 'lxml')

        UserChampionList = soup.find('tbody', class_='Body')
        UserChampionListRows = UserChampionList.find_all('tr')

        i=1
        for UserChampionListRow in UserChampionListRows:
            ChampionName = UserChampionListRow.find(class_='ChampionName Cell').get_text().strip()
            try:  
                wins = int(UserChampionListRow.find(class_='Text Left').get_text()[:-1])
            except AttributeError:
                wins = 0

            try:  
                losses = int(UserChampionListRow.find(class_='Text Right').get_text()[:-1])
            except AttributeError:
                losses = 0

            Kill = float(UserChampionListRow.find(class_='Kill').get_text())
            Death = float(UserChampionListRow.find(class_='Death').get_text())
            Assist = float(UserChampionListRow.find(class_='Assist').get_text())

            try:
                sql = """
                INSERT INTO userCharacterInfo
                    (most_index, nickname, character_name, wins, losses, kills, deaths, assist)
                values
                    (%s, %s, %s, %s, %s, %s, %s, %s)
                """
                cursor.execute(sql, (i, user_nick, ChampionName, wins, losses, Kill, Death, Assist))
            except pymysql.IntegrityError:
                sql = """
                UPDATE userCharacterInfo SET character_name = %s, wins = %s, losses = %s, kills = %s, deaths = %s, assist = %s WHERE most_index = %s AND nickname = %s
                """
                cursor.execute(sql, (ChampionName, wins, losses, Kill, Death, Assist, i, user_nick))
        
            i=i+1

        db.commit()

        return 1

class TcpHandler(socketserver.BaseRequestHandler):
    usermanage = UserManager()

    def handle(self):
        print('ip:%s connected' %self.client_address[0])

        try:
            nickname = self.registerNickname()

            if self.usermanage.crawlUser(nickname) == 1:
                self.request.send('SUCCESS'.encode())

            msg = self.request.recv(1024)
            while msg:
                if self.usermanage.messageHandler(nickname,msg.decode()) == -1 :
                    self.request.close()
                    break
                msg = self.request.recv(1024)

        except Exception as e:
            print(e)

        print('ip:%s Disconnected' %self.client_address[0])
        self.usermanage.removeUser(nickname)


    def registerNickname(self):
        while True:
            self.request.send('you are connected to server'.encode())
            nickname = self.request.recv(1024)
            nickname = nickname.decode().strip()
            if self.usermanage.addUser(nickname,self.request,self.client_address):
                return nickname

class CrawlingServer(socketserver.ThreadingMixIn, socketserver.TCPServer):
    pass

def runServer():
    print('Crawling Server Initialized')
    
    try:
        server = CrawlingServer((HOST,PORT),TcpHandler)#
        server.serve_forever()

    except KeyboardInterrupt:
        print('Crawling Server Exited.')
        server.shutdown()
        server.server_close()

runServer()