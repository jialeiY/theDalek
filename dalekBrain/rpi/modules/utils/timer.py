import time

def timer(func):
    def wrap(*args,**kwargs):
        start=time.time()
        result=func(*args,**kwargs)
        end=time.time()
        print(f"executing time of {func.__name__} is {end-start}")
        return result
        
    return wrap