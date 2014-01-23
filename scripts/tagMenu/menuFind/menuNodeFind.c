tagMenu: menuFind: menuNodeFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"node" ]
#
#Do not load tag records until the end of script
#to prevent ﬂashing of window and to speed up
#script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnKeywordOrNodeFind” (tagMenus) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNodeFind” (tagMenus) ]
End If
#
#Find node tags.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortNode = "cat" or TEMP::sortNode = "" ]
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortNode = "abc" ]
Sort Records [ Speciﬁed Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
January 7, 平成26 16:51:01 Imagination Quality Management.fp7 - menuNodeFind -1-
