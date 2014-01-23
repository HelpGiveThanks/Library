tagMenu: showTag
Commit Records/Requests
If [ TEMP::kfocus = "" ]
Set Field [ TEMP::LocationName; "" ]
Exit Script [ ]
End If
#
#the pulldown menu action selects the id number,
#but not the name. To put the name into the TEMP
#global ﬁeld we will need to ﬁnd it which is what the
#rest of the script does.
Set Variable [ $tag; Value:TEMP::kfocus ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::_Ltag; $tag ]
Perform Find [ ]
Set Variable [ $name; Value:tagTable::tag ]
Go to Layout [ original layout ]
Set Field [ TEMP::LocationName; $name ]
Go to Field [ ]
#
// #Tells user to select an order number not in use
// #if the order ﬁeld is blank.
// If [ TEMP::orderLocation = "" ]
// Show Custom Dialog [ Message: "Order number required. It can be used to place location before or after any modiﬁers: small location or location upstairs for example."; Buttons: “OK” ]
// Go to Field [ TEMP::orderLocation ]
// End If
January 7, 平成26 16:20:36 Imagination Quality Management.fp7 - showTag -1-
