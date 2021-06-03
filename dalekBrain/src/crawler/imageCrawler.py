from selenium import webdriver
import json
import os
import time
import urllib.request
from PIL import Image
from io import BytesIO
import argparse

from urllib.parse import urlparse
from user_agent import generate_user_agent

class BingImageCrawler(object):
    
    def __init__(self):
        
        self.url="https://cn.bing.com/images/search?q={query}"
        self.block_xpath='//ul[@class="dgControl_list"]/li[@data-idx>{data_idx}]'
        self.image_xpath='.//div[@class="imgpt"]/a[@class="iusc"]'
        self.item="m"
        self.item_attr="murl"


    def crawl(self,query,output_dir,maxCount):

        try:
            os.mkdir(output_dir)
        except:
            pass

        links=self._get_links(query,maxCount)
        self._download(links,output_dir)
        
    
    def _get_links(self,query,max_count=1000):
        links=[]
        latest_data_idx=0
        try:
            driver=webdriver.Chrome()
            query_url=self.url.format(query=query)
            driver.get(query_url)

            while len(links)<max_count:

                try:

                    driver.execute_script('window.scrollBy(0, 1000000)')

                    time.sleep(1)

                    image_blocks=driver.find_elements_by_xpath(self.block_xpath.format(data_idx=latest_data_idx))

                    if len(image_blocks)==0:
                        break
                    for image_block in image_blocks:
                        images=image_block.find_elements_by_xpath(self.image_xpath)

                        for image in images:
                            image_item = image.get_attribute(self.item)
                            image_link=json.loads(image_item).get(self.item_attr)
                            if image_link:
                                links.append(image_link)

                        latest_data_idx=int(image_block.get_attribute("data-idx"))
                    print(f"Current total link number: {len(links)}")
                except Exception as e:
                    print(f"craw image error.",str(e))
                
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
    parser = argparse.ArgumentParser(description='Image Crawler')

    # Params for datasets
    parser.add_argument('query', type=str,  help='Search query')
    parser.add_argument('od', type=str,  help='Output directory path')
    parser.add_argument('--max-count', type=int,  default=1000,help='max image count')
    parser.add_argument("--engine", default="bing", type=str, help='select search engine for crawl. Currently support "bing" only')


    args = parser.parse_args()

    query=args.query
    output_dir=args.od
    max_count=args.max_count
    engine=args.engine

    crawler=None
    if engine=="bing":
        crawler=BingImageCrawler()

    if crawler:
        crawler.crawl(query,output_dir,max_count)