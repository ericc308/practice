import urllib.request as req
import bs4
# catch data from movie of ptt
# stringurfront="https://www.vscinemas.com.tw/film/index.aspx?p=1"
stringurfront="https://www.vscinemas.com.tw/vsweb/film/index.aspx"

#stringurlback=".html"
num=7751
numst=str(num)
url = stringurfront
#build request object which have headers's info
request=req.Request(url, headers={
    "User-Agent" : "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36 OPR/58.0.3135.127"
})
with req.urlopen(request) as response:
    data=response.read().decode("utf-8")
#use bs4 to analyze data
#print(data)
    
root = bs4.BeautifulSoup(data, "html.parser") #html.parser help to analyze the code of html type
titles=root.find_all("section", class_="infoArea")
for title in titles:
        if title.h2 !=None:
                         print(title.h2.string)
# for title in titles:
#         if title.h2 !=None:
#             print(title.h2.string)

#print(titles.h2.string)
# for title in titles:
#     if title.a !=None:
#         print(title.a.string) 


#decode data