tagMenu: showTag
Commit Records/Requests
If [ TEMP::kfocus = "" ]
Set Field [ TEMP::LocationName; "" ]
Exit Script [ ]
End If
#
#the pulldown menu action selects the id number,
#but not the name. To put the name into the TEMP
#global field we will need to find it which is what the
#rest of the script does.
Set Variable [ $$stopSetReportNumber; Value:1 ]
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000 ]
Set Variable [ $tag; Value:TEMP::kfocus ]
Set Variable [ $$highlightTestSection ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::_Ltag; $tag ]
Perform Find [ ]
Set Variable [ $name; Value:tagTable::tag ]
Go to Layout [ original layout ]
Set Field [ TEMP::LocationName; $name ]
Close Window [ Current Window ]
Set Variable [ $$stopSetReportNumber ]
Go to Field [ ]
#
// #Tells user to select an order number not in use
// #if the order field is blank.
// If [ TEMP::orderLocation = "" ]
// Show Custom Dialog [ Message: "Order number required. It can be used to place location before or after any modifiers: small location or location upstairs for example."; Buttons: “OK” ]
// Go to Field [ TEMP::orderLocation ]
// End If
July 11, 平成27 23:21:59 Library.fp7 - showTag -1-
