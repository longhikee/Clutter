from tkinter import *

asc = [('null', '0', '0'),
       ('SOH', '1', '1'),
       ('STX', '2', '2'),
       ('ETX', '3', '3'),
       ('EOT', '4', '4'),
       ('ENQ', '5', '5'),
       ('ACK', '6', '6'),
       ('BEL', '7', '7'),
       ('BS', '8', '8'),
       ('HT', '9', '9'),
       ('LF', '10', 'A'),
       ('VT', '11', 'B'),
       ('FF', '12', 'C'),
       ('CR', '13', 'D'),
       ('SO', '14', 'E'),
       ('SI', '15', 'F'),
       ('DLE', '16', '10'),
       ('DC1', '17', '11'),
       ('DC2', '18', '12'),
       ('DC3', '19', '13'),
       ('DC4', '20', '14'),
       ('NAK', '21', '15'),
       ('SYN', '22', '16'),
       ('ETB', '23', '17'),
       ('CAN', '24', '18'),
       ('EM', '25', '19'),
       ('SUB', '26', '1A'),
       ('ESC', '27', '1B'),
       ('FS', '28', '1C'),
       ('GS', '29', '1D'),
       ('RS', '30', '1E'),
       ('US', '31', '1F'),
       ('space', '32', '20'),
       ('!', '33', '21'),
       ('\"', '34', '22'),
       ('#', '35', '23'),
       ('$', '36', '24'),
       ('%', '37', '25'),
       ('&', '38', '26'),
       ('\'', '39', '27'),
       ('(', '40', '28'),
       (')', '41', '29'),
       ('*', '42', '2A'),
       ('+', '43', '2B'),
       (',', '44', '2C'),
       ('-', '45', '2D'),
       ('.', '46', '2E'),
       ('/', '47', '2F'),
       ('0', '48', '30'),
       ('1', '49', '31'),
       ('2', '50', '32'),
       ('3', '51', '33'),
       ('4', '52', '34'),
       ('5', '53', '35'),
       ('6', '54', '36'),
       ('7', '55', '37'),
       ('8', '56', '38'),
       ('9', '57', '39'),
       (':', '58', '3A'),
       (';', '59', '3B'),
       ('<', '60', '3C'),
       ('=', '61', '3D'),
       ('>', '62', '3E'),
       ('?', '63', '3F'),
       ('@', '64', '40'),
       ('A', '65', '41'),
       ('B', '66', '42'),
       ('C', '67', '43'),
       ('D', '68', '44'),
       ('E', '69', '45'),
       ('F', '70', '46'),
       ('G', '71', '47'),
       ('H', '72', '48'),
       ('I', '73', '49'),
       ('J', '74', '4A'),
       ('K', '75', '4B'),
       ('L', '76', '4C'),
       ('M', '77', '4D'),
       ('N', '78', '4E'),
       ('O', '79', '4F'),
       ('P', '80', '50'),
       ('Q', '81', '51'),
       ('R', '82', '52'),
       ('S', '83', '53'),
       ('T', '84', '54'),
       ('U', '85', '55'),
       ('V', '86', '56'),
       ('W', '87', '57'),
       ('X', '88', '58'),
       ('Y', '89', '59'),
       ('Z', '90', '5A'),
       ('[', '91', '5B'),
       ('\\', '92', '5C'),
       (']', '93', '5D'),
       ('^', '94', '5E'),
       ('_', '95', '5F'),
       ('`', '96', '60'),
       ('a', '97', '61'),
       ('b', '98', '62'),
       ('c', '99', '63'),
       ('d', '100', '64'),
       ('e', '101', '65'),
       ('f', '102', '66'),
       ('g', '103', '67'),
       ('h', '104', '68'),
       ('i', '105', '69'),
       ('j', '106', '6A'),
       ('k', '107', '6B'),
       ('l', '108', '6C'),
       ('m', '109', '6D'),
       ('n', '110', '6E'),
       ('o', '111', '6F'),
       ('p', '112', '70'),
       ('q', '113', '71'),
       ('r', '114', '72'),
       ('s', '115', '73'),
       ('t', '116', '74'),
       ('u', '117', '75'),
       ('v', '118', '76'),
       ('w', '119', '77'),
       ('x', '120', '78'),
       ('y', '121', '79'),
       ('z', '122', '7A'),
       ('{', '123', '7B'),
       ('|', '124', '7C'),
       ('}', '125', '7D'),
       ('~', '126', '7E'),
       ('DEL', '127', '7F')
      ]

class Ascii:
  def __init__(self):
    self.master = Tk()
    self.sw = self.master.winfo_screenwidth() #screen width
    self.sh = self.master.winfo_screenheight() #screen height
    x = (self.sw - 300) / 2
    y = (self.sh - 200) / 2
    #window centralized
    self.master.geometry("%dx%d+%d+%d" % (300, 200, x, y))
    self.master.title('ASCII')

    self.frm = Frame(self.master)
    #top
    Label(self.master, text='Ascii Query', font=('Arial', 15)).pack()

    #left
    self.var_L = StringVar()
    self.frm_L = Frame(self.frm)
    Label(self.frm_L, text = 'Charactor', font=('Arial', 12)).pack()
    self.e_L = Entry(self.frm_L, textvariable=self.var_L, width=5, font=('Verdana', 15))

    #middle
    self.var_M = StringVar()
    self.frm_M = Frame(self.frm)
    Label(self.frm_M, text = 'Dec', font=('Arial', 12)).pack()
    self.e_M = Entry(self.frm_M, textvariable=self.var_M, width=5, font=('Verdana', 15))

    #right
    self.var_R = StringVar()
    self.frm_R = Frame(self.frm)
    Label(self.frm_R, text = 'Hex', font=('Arial', 12)).pack()
    self.e_R = Entry(self.frm_R, textvariable=self.var_R, width=5, font=('Verdana', 15))

    #bottom
    self.frm_B = Frame(self.master)
    Button(self.frm_B, text='clear', command=self.clear, width=6, height=1, font=('Arial', 10)).pack(side=LEFT)
    Button(self.frm_B, text='query', command=self.query, width=6, height=1, font=('Arial', 10)).pack(side=RIGHT)
    #bind hot key
    self.master.bind("<Return>", self.enter_event)
    self.master.bind("<BackSpace>", self.back_event)

   

    self.frm.pack()
    self.frm_L.pack(side=LEFT)
    self.frm_R.pack(side=RIGHT)
    self.frm_M.pack(side=RIGHT)
    self.frm_B.pack(side=BOTTOM)
#    self.frm_B.pack(anchor=CENTER)
    self.e_L.pack()
    self.e_M.pack()
    self.e_R.pack()

  def back_event(self, evnet):
    if self.e_L['state'] == 'readonly' :
      self.clear()

  def clear(self):
    self.var_L.set('')
    self.var_M.set('')
    self.var_R.set('')
    self.e_L['state'] = 'normal'
    self.e_M['state'] = 'normal'
    self.e_R['state'] = 'normal'

  def enter_event(self, event):
    if self.e_L['state'] != 'readonly' :
      self.query()

  def query(self):
    self.e_L['state'] = 'readonly'
    self.e_M['state'] = 'readonly'
    self.e_R['state'] = 'readonly'
    (l, m, r) = self.translate()
    if (l, m, r) == ('nul', 'nul', 'nul') :
      self.clear()
    else :
      self.var_L.set(l)
      self.var_M.set(m)
      self.var_R.set(r)

  def translate(self):
    l = self.var_L.get()
    r = self.var_R.get()
    m = self.var_M.get()
    if l == '' and m == '' and r == '' :
      #print('all input is empty')
      return ('nul', 'nul', 'nul')
    elif l != '' :
      return self.search(l, 0)

    elif m != '' :
      return self.search(m, 1)

    elif r != '' :
      return self.search(r, 2)

  def search(self, key, pos):
    for s in asc :
      if s[pos] == key :
        return s
    
    if pos == 0:
      err = 'charactor ' + key
    elif pos == 1:
      err = 'Oct ' + key
    elif pos == 2:
      err = 'Hex ' + key
    self.errMsgBox(err)
    return ('', '', '')

  def close(self):
    self.top.destroy()
    
  def errMsgBox(self, err):
    self.clear()
    self.top = Toplevel()
    lb = Label(self.top, text=err + ' is invalid', font=('Arial', 15))
    self.top.title("Error")
    x = (self.sw - 300) / 2 + 100
    y = (self.sh - 80) /2 - 200
    self.top.geometry('300x80+%d+%d' % (x, y))
    lb.pack()
    Button(self.top, text='close', command=self.close).pack()
    self.master.after(5000,self.top.destroy)  #close top after 5 second automatically

def main():
  asc = Ascii()
  mainloop()

if __name__ == "__main__":
  main()
