try:
    print("Let's")
    raise NameError("thre")
except NameError:
    print("An ex")
    raise
else:
    print("he again")
finally:
    print("final")
