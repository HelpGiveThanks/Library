January 15, 2018 17:16:27 Library.fmp12 - selectTestSection -1-
tagMenu: selectTestSection
#
#If user deleted field contents,
#then exit this script.
Commit Records/Requests
If [ TEMP::kdefaultSectionTemplate = "" ]
Set Field [ TEMP::DEFAULTSectionName; "" ]
Exit Script [ ]
End If
#
#The pulldown menu action selects the ID number,
#but not the name. To put the name into the TEMP
#global field we will need to find it, which is what the
#rest of the script does.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
Set Variable [ $tag; Value:TEMP::kdefaultSectionTemplate ]
#
#Remove highlight telling user
#to select a section.
Set Variable [ $$highlightTestSection ]
#
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::_Ltag; $tag ]
Perform Find [ ]
#
Set Variable [ $name; Value:tagTable::tag ]
#
Go to Layout [ original layout ]
Set Field [ TEMP::DEFAULTSectionName; $name ]
#
Close Window [ Current Window ]
Set Variable [ $$stopLoadTestRecord ]
#
Go to Field [ ]
#
