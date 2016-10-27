# RemoteControl
A RemoteControl software which can realize using local keybord and mouse to control remote PC in local area network. This software is based on UDP protocol.

##Control
  软件分控制端和接收端两部分，控制端运行后会全屏显示，这时移动鼠标或按下键盘按键都会传输到接收端，键盘没有屏蔽windows键和部分系统热键
  
##Receive
  在接收端运行即可，目前接收端和控制端需要在同一个网段中，广域网中不可使用，可以有多个接收端和控制端，控制端同时动作时会发生干扰
