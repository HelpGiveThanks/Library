tagMenu: findMode
#
If [ $$findMode= "" ]
#
#
#
#
#If find mode is active then return to browse mode.
If [ Get ( WindowMode ) = 1 ]
#
#If user presses enter find button then perform the
#steps below to complete the find.
Perform Find [ ]
Go to Layout [ $$findLayout ]
Set Variable [ $$findLayout ]
#
#Sort reference or tag records depending on which
#records user is viewing.
If [ Get (LayoutTableName) = "reference" ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Halt Script
Else
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Halt Script
End If
#
#If user presses enter find button then perform the
#steps below to complete the find.
End If
#
#Ask user if they want to find a tag or find learn items
#tagged with specific tags (except if they are in test).
If [ Get (LayoutTableName) ≠ "test" ]
#
#Show different message for learn and reference sections.
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
Show Custom Dialog [ Message: "Find tagged learn records OR find tag(s)? "; Buttons: “tag(s)”, “learn”, “cancel” ]
#
Else If [ Left (Get (LayoutName) ; 9 ) = "reference" and $$referenceRecordOne ≠ 2 ]
#
#Eliminate find reference option for citation menu.
If [ $$citationMatch ≠ "cite" ]
Show Custom Dialog [ Message: "Find tagged reference records OR find tag(s)? "; Buttons: “tag(s)”, “reference”, “cancel” ]
Else
Show Custom Dialog [ Message: "Find tag(s)? "; Buttons: “cancel”, “tag(s)” ]
End If
End If
#
#If user selects to find tags enter find mode first.
If [ Get ( LastMessageChoice ) = 1 and $$ClearMessageChoice ≠ 2 ]
Enter Find Mode [ ]
#
#Determine if user is looking tag or reference records.
If [ Get (LayoutTableName) = "reference" ]
#
#Get the layout name for the return trip after find is done.
Set Variable [ $$findLayout; Value:Get (LayoutName) ]
#
#Show different layouts for learn and reference tag
#menu items.
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
Go to Layout [ “learnMenuFINDref” (reference) ]
Else
Go to Layout [ “referenceMenuFINDref” (reference) ]
End If
#
#Limit search to only items user selected to show in
#learn mode if in learn mode.
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::show; "show in learn" ]
#
Else
#Show all reference items for a section if in
#reference mode.
Set Field [ reference::kcsection; TEMP::ksection ]
End If
#
#Select the field where the user needs to enter the
#find information.
Go to Field [ reference::referenceForReferenceWindow ]
#
#Pause and wait until user is ready to perform find.
Pause/Resume Script [ Indefinitely ]
#
#If user presses enter key then perform the steps below
#to complete the find.
Perform Find [ ]
Go to Layout [ $$findLayout ]
Set Variable [ $$findLayout ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Halt Script
Exit Script [ ]
#
Else
#Limit search to only items user selected to show in
#learn mode if in learn mode.
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Set Variable [ $$findLayout; Value:Get (LayoutName) ]
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
If [ Left (Get (LayoutName) ; 5 ) = "learn" ]
Go to Layout [ “learnMenuFINDrefLearn” (testlearn) ]
#Clear these variables so find will work.
Set Field [ tagMenus::match; "" ]
Set Field [ ruleTagMenuGroups::ksection; "" ]
Else
Go to Layout [ “ltagFINDNK” (tagMenus) ]
End If
#
Else
August 1, 平成26 9:54:21 Imagination Quality Management.fp7 - findMode -1-tagMenu: findMode
#Show all reference items for a section if in
#reference mode.
Go to Layout [ “referenceFINDNK” (tagMenus) ]
End If
#
#Select the field where the user needs to enter the
#find information.
If [ Left (Get (LayoutName) ; 5 ) = "learn" ]
Go to Field [ testlearn::Caption ]
Else
Go to Field [ tagMenus::tag ]
End If
#
#Pause and wait until user is ready to perform find.
Pause/Resume Script [ Indefinitely ]
#
#If user presses enter key then perform the steps below
#to complete the find.
Perform Find [ ]
Go to Layout [ $$findLayout ]
Set Variable [ $$findLayout ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Exit Script [ ]
End If
#
Else If [ Get ( LastMessageChoice ) = 3 ]
#If user cancels then exit exit.
Exit Script [ ]
End If
End If
#
#
#
#
#So if user wants to find learn records, then go into
#menu for finding learn records by green button tags.
#
#Find must be done for tags, so if user is showing no
#tags when find is activitated then take user to keywords
#tag menu.
If [ Get (LayoutName) = "ReferenceMenuNoTags" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
End If
#
Set Variable [ $$findMode; Value:1 ]
Set Variable [ $$findLayout; Value:Get (LayoutName) ]
If [ Right ( Get (LayoutName) ; 7 ) = "refcite" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “learnMenu4RefCiteFindTL” (testlearn) ]
Else If [ Right ( Get (LayoutName) ; 5 ) = "menu1" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “learnFind” (tagMenus) ]
Else If [ Right ( Get (LayoutName) ; 6 ) = "sample" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “learnFindSample” (tagMenus) ]
Else If [ Left ( Get (LayoutName) ; 6 ) = "ltagNK" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “learnKeywordOrNodeFind” (tagMenus) ]
Else If [ Right ( Get (LayoutName) ; 1 ) = "3" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “learnKeywordOrNodeFind” (tagMenus) ]
Else If [ Right ( Get (LayoutName) ; 4 ) = "test" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “learnFindTest” (test) ]
Else If [ Right ( Get (LayoutName) ; 5 ) = "3cite" and Left ( Get (LayoutName) ; 1 ) = "l" ]
Go to Layout [ “learnFindCite” (reference) ]
#
#
Else If [ Right ( Get (LayoutName) ; 5 ) = "menu1" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Go to Layout [ “ReferenceMenuFind” (tagMenus) ]
Else If [ Right ( Get (LayoutName) ; 5 ) = "node1" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNodeFind” (tagMenus) ]
Else If [ Right ( Get (LayoutName) ; 5 ) = "node2" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNodeFind” (tagMenus) ]
Else If [ Right ( Get (LayoutName) ; 1 ) = "3" and Left ( Get (LayoutName) ; 1 ) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNodeFind” (tagMenus) ]
End If
#
#Clear the first record question variable so user will
#not be asked if they wish to find or tag reference records.
Set Variable [ $$referenceRecordOne ]
Set Variable [ $$ClearMessageChoice ]
#
#As going to the other window will be involved
#stop the record load script on that window until
#this script is finished to speed things up and
#stop flashing effect.
// Set Variable [ $$stoploadCitation; Value:1 ]
Select Window [ Name: "References"; Current file ]
If [ Get (LayoutName) = "ReferenceEDIT" ]
Go to Layout [ “Reference” (reference) ]
End If
Select Window [ Name: "Learn"; Current file ]
If [ Get (LayoutName) = "Learn4Edit" ]
Go to Layout [ “learn4” (testlearn) ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
Else If [ $$findMode= 1 ]
Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Go to Layout [ $$findLayout ]
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
End If
#
August 1, 平成26 9:54:21 Imagination Quality Management.fp7 - findMode -2-