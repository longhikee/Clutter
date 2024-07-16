class Files:
  def __init__(self,**kwargs):
    self.properties = kwargs

  def copy(self):
    print('copying')
  def move(self):
    print('moving')
  def remove(self):
    print(deleting)

  def get_properties(self):
    return self.properties
  def get_property(self,key):
    return self.properties.get(key,None)


  @property
  def privacy(self):
    return self.properties.get('privacy',None)

  @privacy.setter
  def privacy(self,c):
    self.properties['privacy'] = c

  @privacy.setter
  def privacy(self):
    del self.properties["privacy"]


imageDoc = Files(privacy="secret")
print(imageDoc.get_property("privacy"))

print()

doc = Files()
doc.privacy = "archive"
print(doc.privacy)
