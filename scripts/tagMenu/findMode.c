tagMenu: FindMode
#
If [ $$ﬁndMode= "" ]
#
#
#
#
#If ﬁnd mode is active then return to browse mode.
If [ Get ( WindowMode ) = 1 ]
#
#If user presses enter ﬁnd button then perform the
#steps below to complete the ﬁnd.
Perform Find [ ]
Go to Layout [ $$ﬁndLayout ]
Set Variable [ $$ﬁndLayout ]
#
#Sort reference or tag records depending on which
#records user is viewing.
If [ Get (LayoutTableName) = "reference" ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::orderOrLock; ascending
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Halt Script
Else
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Halt Script
End If
#
#If user presses enter ﬁnd button then perform the
#steps below to complete the ﬁnd.
End If
#
#Ask user if they want to ﬁnd a tag or ﬁnd learn items
#tagged with speciﬁc tags (except if they are in test).
If [ Get (LayoutTableName) ≠ "test" ]
#
#Show different message for learn and reference sections.
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
Show Custom Dialog [ Message: "Find tagged learn records OR ﬁnd tag(s)? "; Buttons: “learn”, “tag(s)”, “cancel” ]
#
Else If [ Left (Get (LayoutName) ; 9 ) = "reference" and $$referenceRecordOne ≠ 1 ]
#
#Eliminate ﬁnd reference option for citation menu.
If [ $$citationMatch ≠ "cite" ]
Show Custom Dialog [ Message: "Find tagged reference records OR ﬁnd tag(s)? "; Buttons: “reference”, “tag(s)”, “cancel” ]
Else
Show Custom Dialog [ Message: "Find tag(s)? "; Buttons: “cancel”, “tag(s)” ]
End If
End If
#
#If user selects to ﬁnd tags enter ﬁnd mode ﬁrst.
If [ Get ( LastMessageChoice ) = 2 and $$ClearMessageChoice ≠ 1 ]
Enter Find Mode [ ]
#
#Determine if user is looking tag or reference records.
If [ Get (LayoutTableName) = "reference" ]
#
#Get the layout name for the return trip after ﬁnd is done.
Set Variable [ $$ﬁndLayout; Value:Get (LayoutName) ]
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
#Select the ﬁeld where the user needs to enter the
#ﬁnd information.
Go to Field [ reference::referenceForReferenceWindow ]
#
#Pause and wait until user is ready to perform ﬁnd.
Pause/Resume Script [ Indeﬁnitely ]
#
#If user presses enter key then perform the steps below
#to complete the ﬁnd.
Perform Find [ ]
Go to Layout [ $$ﬁndLayout ]
Set Variable [ $$ﬁndLayout ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::orderOrLock; ascending
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
Set Variable [ $$ﬁndLayout; Value:Get (LayoutName) ]
If [ Left (Get (LayoutName) ; 9 ) ≠ "reference" ]
If [ Left (Get (LayoutName) ; 5 ) = "learn" ]
Go to Layout [ “learnMenuFINDrefLearn” (testlearn) ]
#Clear these variables so ﬁnd will work.
Set Field [ tagMenus::match; "" ]
Set Field [ ruleTagMenuGroups::ksection; "" ]
Else
Go to Layout [ “ltagFINDNK” (tagMenus) ]
End If
#
Else
January 7, 平成26 16:39:01 Imagination Quality Management.fp7 - FindMode -1-tagMenu: FindMode
#Show all reference items for a section if in
#reference mode.
Go to Layout [ “referenceFINDNK” (tagMenus) ]
End If
#
#Select the ﬁeld where the user needs to enter the
#ﬁnd information.
If [ Left (Get (LayoutName) ; 5 ) = "learn" ]
Go to Field [ testlearn::Caption ]
Else
Go to Field [ tagMenus::tag ]
End If
#
#Pause and wait until user is ready to perform ﬁnd.
Pause/Resume Script [ Indeﬁnitely ]
#
#If user presses enter key then perform the steps below
#to complete the ﬁnd.
Perform Find [ ]
Go to Layout [ $$ﬁndLayout ]
Set Variable [ $$ﬁndLayout ]
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
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
#So if user wants to ﬁnd learn records, then go into
#menu for ﬁnding learn records by green button tags.
#
#Find must be done for tags, so if user is showing no
#tags when ﬁnd is activitated then take user to keywords
#tag menu.
If [ Get (LayoutName) = "ReferenceMenuNoTags" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
End If
#
Set Variable [ $$ﬁndMode; Value:1 ]
Set Variable [ $$ﬁndLayout; Value:Get (LayoutName) ]
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
#Clear the ﬁrst record question variable so user will
#not be asked if they wish to ﬁnd or tag reference records.
Set Variable [ $$referenceRecordOne ]
Set Variable [ $$ClearMessageChoice ]
#
#As going to the other window will be involved
#stop the record load script on that window until
#this script is ﬁnished to speed things up and
#stop ﬂashing effect.
// Set Variable [ $$stoploadCitation; Value:1 ]
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LayoutName) = "ReferenceEDIT" ]
Go to Layout [ “Reference” (reference) ]
End If
Select Window [ Name: "Learn"; Current ﬁle ]
If [ Get (LayoutName) = "Learn4Edit" ]
Go to Layout [ “learn4” (testlearn) ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Exit Script [ ]
Else If [ $$ﬁndMode= 1 ]
Set Variable [ $$ﬁndMode ]
Set Variable [ $$ﬁrstFind ]
Set Variable [ $$ﬁrstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Go to Layout [ $$ﬁndLayout ]
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
End If
#
January 7, 平成26 16:39:01 Imagination Quality Management.fp7 - FindMode -2-
