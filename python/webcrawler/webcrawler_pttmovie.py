import urllib.request as req
import bs4
# catch data from movie of ptt
stringurfront="https://www.ptt.cc/bbs/movie/index"
stringurlback=".html"
num=7751

for num in range (7751,7749, -1):
    #url = "https://www.ptt.cc/bbs/movie/index7751.html"
    numst=str(num)
    url = stringurfront+numst+stringurlback
    #build request object which have headers's info
    request=req.Request(url, headers={
    "User-Agent" : "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36 OPR/58.0.3135.127"
    })
    with req.urlopen(request) as response:
        data=response.read().decode("utf-8")
    #use bs4 to analyze data
    
    root = bs4.BeautifulSoup(data, "html.parser") #html.parser help to analyze the code of html type
    titles=root.find_all("div", class_="title")
    for title in titles:
        if title.a !=None:
            print(title.a.string)


#decode data