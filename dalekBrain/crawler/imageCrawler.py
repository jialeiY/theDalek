from selenium import webdriver
import json
import os
import time
import urllib.request
from PIL import Image
from io import BytesIO

from urllib.parse import urlparse
from user_agent import generate_user_agent

class BingImageCrawler(object):
    
    def __init__(self):
        
        self.url="https://cn.bing.com/images/search?q={query}"
        self.block_xpath='//div[@class="imgpt"]/a[@class="iusc"]'
        self.item="m"
        self.item_attr="murl"


    def crawl(self,query,output_dir,maxCount):

        links=self._get_links(query,maxCount)
        self._download(links,output_dir)
        
    
    def _get_links(self,query,max_count=1000,min_count=100):
        links=[]
        try:
            driver=webdriver.Chrome()
            query_url=self.url.format(query=query)
            driver.get(query_url)

            

            while len(links)<min_count:

                driver.execute_script('window.scrollBy(0, 1000000)')
                time.sleep(1)

                image_blocks=driver.find_elements_by_xpath(self.block_xpath)

                for image_block in image_blocks:
                    image_item = image_block.get_attribute(self.item)
                    image_link=json.loads(image_item).get(self.item_attr)
                    if image_link:
                        links.append(image_link)
                    if(len(links)>max_count):
                        break
                
            return links

        finally:
            driver.close()
    
    def _download(self,links,output_dir):
        os.makedirs(output_dir,exist_ok=True)

        headers = {}

        for i,link in enumerate(links):
            try:

                parse = urlparse(link)
                ref = parse.scheme + '://' + parse.hostname
                ua = generate_user_agent()
                headers['User-Agent'] = ua
                headers['referer'] = ref
                req = urllib.request.Request(link, headers=headers)
                with urllib.request.urlopen(req,timeout=5) as r:

                    data = r.read()

                    image = Image.open(BytesIO(data)).convert('RGB')

                    ext = link.split('.')[-1]
                    image_path = os.path.join(output_dir, f"{i}.jpg")
                    image.save(image_path)

                print(f"downloaded {i} image")
                                         
            # handle exceptions
            except Exception as e:
                print(f"not download: {link}",e)





if __name__=="__main__":
    crawler=BingImageCrawler()
    crawler.crawl("daleks","/Users/jialeiyang/Documents/projects/theDalek/dalekBrain/data/daleks",1000)