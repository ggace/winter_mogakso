from selenium import webdriver
from bs4 import BeautifulSoup as bs
from openpyxl import Workbook


options = webdriver.ChromeOptions()
options.add_argument("headless")
driver = webdriver.Chrome('score_info\chromedriver.exe', options=options)
url = 'https://ipsi.jinhak.or.kr/subList/20000000095'
driver.get(url)
driver.implicitly_wait(time_to_wait=1000)
driver.find_element(by='id', value='pass').click()
driver.find_element(by='id', value='srchbtn').click()


wb = Workbook()
sheet = wb.active



school_score = {}


def scrap_10_page():
    for page_count in range(3,13):
        element = driver.find_element(by='css selector', value=f'#list_area > ul > li:nth-child({page_count}) > a')
        driver.execute_script("arguments[0].click();", element)
        html = driver.page_source
        soup = bs(html, "html.parser")
        for i in range(1,16):
            school_name = soup.select_one(f'#list_area > div > table > tbody > tr:nth-child({i}) > td:nth-child(4)').text
            score_info = float(soup.select_one(f'#list_area > div > table > tbody > tr:nth-child({i}) > td:nth-child(11)').text)
            try:
                school_score[school_name][0] += 1
                school_score[school_name][1] += score_info
            except:
                school_score[school_name] = [1, score_info]
        print(f'page{count_page*10+page_count-2} - success')


for count_page in range(163):
    scrap_10_page()
    for line, (key, value) in enumerate(school_score.items()):
        sheet[f'A{line+1}'] = key
        sheet[f'B{line+1}'] = str(round(value[1]/value[0], 2))
    element = driver.find_element(by='css selector', value='#list_area > ul > li:nth-child(13) > a')
    driver.execute_script("arguments[0].click();", element)
    wb.save('C:/Users/H/OneDrive/바탕 화면/visual_studio_code/website/score_info/score.xlsx')



for school, score in school_score.items():
    print(school+':'+str(round(score[1]/score[0], 2)))
driver.quit()
