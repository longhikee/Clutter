class data:

        def __init__(self,value):
                self._v=value
                print("constructor ")

        def create(self):
                print("creating data ",self._v)
        def update(self):
                print("updating data")
        def delete(self):
                print("removing data")


custerData = data(10)
custerData.create()
custerData.update()
custerData.delete()

