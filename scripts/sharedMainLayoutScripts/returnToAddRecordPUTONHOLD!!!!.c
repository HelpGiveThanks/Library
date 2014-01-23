sharedMainLayoutScripts: returnToAddRecordPUTONHOLD!!!!
#
#I've decided to not continue ﬁnishing this script.
#The idea was if the user navigated away from
#the record they came into add mode to add to
#this script would focus back on that record.
#Part of the reason for this was that in add mode
#The database was set to just keyword or node
#in terms of noting the FilterFind ﬁeld. But that
#has now been made by dynamic by tying this noting
#to the citation match ﬁeld. If later on this seems
#useful this script can be polished for use. Right
#now it just seems like giving the user too much
#help, which looks like to many buttons on the layout!
#
If [ $$addCitationMatch = "node" and $$addCitationMatch ≠ $$CitationMatch ]
#
#
Select Window [ Name: "Tag Menus"; Current ﬁle ]
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
If [ TEMP::layoutRtagN = "" or TEMP::layoutLtagN = "" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
End If
#
Else If [ TEMP::layoutRtagN ≠ "" or TEMP::layoutLtagN ≠ "" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ TEMP::layoutLtagN ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ TEMP::layoutRtagN ]
End If
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
#If no records exist then create one.
If [ Get (FoundCount)=0 ]
Perform Script [ “newCitationMenuGroup” ]
End If
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortNode = "cat" ]
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
#
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$addRecord = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Inform user of items use on both screens.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord” ]
#
#Just in case user was in nonTag ﬁeld on this
#window when user clicked a menu button on
#the other window, exit all ﬁelds.
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:reference::knodePrimary ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
#
Else If [ $$addCitationMatch = "key" and $$addCitationMatch ≠ $$CitationMatch ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"key" ]
#
#Do not load tag records until the end of script
#to prevent ﬂashing of window and to speed up
#script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Goto correct layout.
If [ TEMP::layoutRtagK = "" or TEMP::layoutLtagK = "" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
End If
#
Else If [ TEMP::layoutRtagK ≠ "" or TEMP::layoutLtagK ≠ "" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ TEMP::layoutLtagK ]
January 7, 平成26 18:07:28 Imagination Quality Management.fp7 - returnToAddRecordPUTONHOLD!!!! -1-sharedMainLayoutScripts: returnToAddRecordPUTONHOLD!!!!
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ TEMP::layoutRtagK ]
End If
End If
#
#Find key tags for library section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
#If no records exist then create one.
If [ Get (FoundCount)=0 ]
Perform Script [ “newCitationMenuGroup” ]
End If
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortKey = "cat" ]
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortKey = "abc" ]
Sort Records [ Speciﬁed Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$addRecord = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Inform user of items use on both screens.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord” ]
#
#Just in case user was in nonTag ﬁeld on this
#window when user clicked a menu button on
#the other window, exit all ﬁelds.
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kKeywordPrimary ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:reference::kkeywordPrimary ]
End If
Refresh Window
#
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
Else If [ $$addCitationMatch = "testItem" and $$addCitationMatch ≠ $$CitationMatch ]
#
#Goto correct layout.
If [ TEMP::DetailmoreORLessLayout = "" ]
Go to Layout [ “setupTestItem” (tagMenus) ]
Else If [ TEMP::DetailmoreORLessLayout ≠ "" ]
Go to Layout [ TEMP::DetailmoreORLessLayout ]
End If
Set Variable [ $$citationMatch; Value:"testItem" ]
#
#Find detail tags for library section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::kGroupOrTest; TEMP::ktestItemList ]
Perform Find [ ]
#
#If no records exist then create one.
If [ Get (FoundCount)=0 ]
Perform Script [ “newCitationMenuGroup” ]
End If
#
Sort Records [ Speciﬁed Sort Order: ruleTagMenuTestGroups::order; based on value list: “order”
ruleTagMenuTestGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$addRecord = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
January 7, 平成26 18:07:28 Imagination Quality Management.fp7 - returnToAddRecordPUTONHOLD!!!! -2-
