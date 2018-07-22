July 21, 2018 14:17:34 Library.fmp12 - reviewCopyright -1-
tagMenu: reviewCopyright
#
#
#Clear all add mode variables just in case user
#just ran the add pictures and links script.
Set Variable [ $$tagLayout ]
Set Variable [ $$returnLayout ]
Set Variable [ $$returnRecord ]
Set Variable [ $$returnWindow ]
Set Variable [ $$userInCopyrightWindow ]
#
#Essential to show user a copyright versus test
#item lock message when this script is triggered
#informUserHowToEditLockedLayoutText.
Set Variable [ $$showCopyrightLockMessage; Value:1 ]
#
#
#
#BEGIN Get copyright key
#
#
#
#If the copyright tag's creator is a locked node,
#the creator node's orderOrLock field will have
#zero — 0 — in it.
#
#Capture the copyright's key for finding it
#in the copyright review window in every
#section.
#
#
#
#1) Default Section (A, B, and C) ...
# and Reference Section ( B ) ...
# A
#... tag menus window — alldefaults
If [ Get (LayoutTableName) = "tempSetup" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:TEMP::kdefaultCopyright ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ defaultNodesCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ defaultNodeCopyrightsCreatorLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; defaultNodeCopyrightsCreatorLock::tag ]
#
Else If [ defaultNodesCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
defaultNodeCopyrightsCreatorLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; defaultNodeCopyrightsCreatorLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
# B
#... tag menus window — copyright
If [ Get (LayoutTableName) = "tagMenus" and $$citationMatch = "copyright" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:tagMenus::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ tagMenus::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ tagCreatorLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; tagCreatorLock::tag ]
#
Else If [ tagMenus::kRecordCreatorNode ≠ "defaultCopyright"
 and
tagCreatorLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; tagCreatorLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
# C
#... tag menus window — node
If [ Get (LayoutTableName) = "tagMenus" and $$citationMatch = "node" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:tagsCopyright::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ tagsCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ tagCopyrightsCreatorLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; tagCopyrightsCreatorLock::tag ]
#
Else If [ tagsCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
tagCopyrightsCreatorLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; tagCopyrightsCreatorLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
#
#2) Learn Section (A and B) ...
# A
#... main learn window
If [ Get (LayoutTableName) = "testlearn" and Get (WindowName) = "Learn"
 or
Get (LayoutTableName) = "testlearn" and Get (WindowName) = "Edit" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:learnCreatorsCopyright::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ learnCreatorsCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ learnCopyrightCreatorsCopyrightLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; learnCopyrightCreatorsCopyrightLock::tag ]
#
Else If [ learnCreatorsCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
learnCopyrightCreatorsCopyrightLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; learnCopyrightCreatorsCopyrightLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
# B
#... tag menus window — brainstorm
If [ Get (LayoutTableName) = "tagMenus" and $$citationMatch = "brainstorm" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:tagsCopyright::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ tagsCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ tagCopyrightsCreatorLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; tagCopyrightsCreatorLock::tag ]
#
Else If [ tagsCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
tagCopyrightsCreatorLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; tagCopyrightsCreatorLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
#
#3) Setup Test Section (A, B, and C) ...
# A
#... main setup window
If [ Get (LayoutTableName) = "testSubsectionTemplate" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:testSectionCreatorsCopyright::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ testSectionCreatorsCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ testSectionCopyrightsCreatorLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; testSectionCopyrightsCreatorLock::tag ]
#
Else If [ testSectionCreatorsCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
testSectionCopyrightsCreatorLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; testSectionCopyrightsCreatorLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
# B
#... tag menus window — section
If [ Get (LayoutTableName) = "testSection" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:testSectionCreatorsCopyright::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ testSectionCreatorsCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ testSectionCopyrightsCreatorLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; testSectionCopyrightsCreatorLock::tag ]
#
Else If [ testSectionCreatorsCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
testSectionCopyrightsCreatorLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; testSectionCopyrightsCreatorLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
# C
#... tag menus window — item
If [ Get (LayoutTableName) = "tagMenus" and $$citationMatch = "testItem" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:tagCreatorsCopyright::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ tagCreatorsCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ tagCreatorsCopyrightsCreatorLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; tagCreatorsCopyrightsCreatorLock::tag ]
#
Else If [ tagCreatorsCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
tagCreatorsCopyrightsCreatorLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; tagCreatorsCopyrightsCreatorLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
#
#4) Test Section ( A ) ...
# A
#... main test window
If [ Get (LayoutTableName) = "testlearn" and Get (WindowName) = "Test" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:learnTestSubjectCopyright::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ learnTestSubjectCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ learnTestSubjectCopyrightCreatorsCopyrightLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; learnTestSubjectCopyrightCreatorsCopyrightLock::tag ]
#
Else If [ learnTestSubjectCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
learnTestSubjectCopyrightCreatorsCopyrightLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; learnTestSubjectCopyrightCreatorsCopyrightLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
#
#5) Report Section (A and B) ...
# A
#... main report window
If [ Get (LayoutTableName) = "report" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:reportTestSubjectCopyright::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ reportTestSubjectCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ reportTestSubjectCreatorCopyrightLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; reportTestSubjectCreatorCopyrightLock::tag ]
#
Else If [ reportTestSubjectCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
reportTestSubjectCreatorCopyrightLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; reportTestSubjectCreatorCopyrightLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
# B
#... tag menus window — result
If [ Get (LayoutTableName) = "testlearnReportTags" ]
#
#Get copyright's key for finding it below.
Set Variable [ $copyright; Value:reportResultTestSubjectCopyright::_Ltag ]
#
#Now capture locked/unlocked status and
#who created it from 3 possibilities:
If [ reportResultTestSubjectCopyright::kRecordCreatorNode = "defaultCopyright" ]
#a) Locked library default copyright, get library version
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; "Library " & tempSetup::versionNumber ]
#
Else If [ reportResultTestSubjectCreatorCopyrightLock::orderOrLock ≠ "" ]
#b) Locked user copyright, get creator's name
#to display as copyright creator.
Set Field [ TEMP::copyrightCreatorsName; reportResultTestSubjectCreatorCopyrightLock::tag ]
#
Else If [ reportResultTestSubjectCopyright::kRecordCreatorNode ≠ "defaultCopyright"
 and
reportResultTestSubjectCreatorCopyrightLock::orderOrLock = "" ]
#c) Unlocked user copyright, get creator's name
#to display as copyright creator, and set unlock
#variable so unlocked review layout is shown.
Set Field [ TEMP::copyrightCreatorsName; reportResultTestSubjectCreatorCopyrightLock::tag ]
Set Variable [ $unlocked; Value:1 ]
End If
#
End If
#
#
#
#END Get copyright key
#
#
#
#
#
#
#BEGIN Find copyright and review it
#
#
#
#If the user hasn't selected a copyright,
#then exit the script.
If [ $copyright = "" ]
Close Window [ Name: "Copyright"; Current file ]
Exit Script [ ]
End If
#
#Stop record loading scripts.
Set Variable [ $$stopTest; Value:1 ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Closer this window just in case a copy of it
#is open, and then open a new one.
Close Window [ Name: "Copyright"; Current file ]
New Window [ Name: "Copyright"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
#
#Show just the copyright of interest in the
#locked or unlocked window.
If [ $unlocked = "" ]
Go to Layout [ “CopyrightVIEW” (tagMenus) ]
Else
Go to Layout [ “CopyrightEDIT” (tagMenus) ]
End If
Enter Find Mode [ ]
Set Field [ tagMenus::_Ltag; $copyright ]
Perform Find [ ]
#
#Start record loading scripts.
Set Variable [ $$stopTest ]
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#If this is a new tag then enter the tag field so
#user knows where to start entering information
#for their new tag.
If [ $unlocked ≠ "" and tagMenus::tag = "" ]
Go to Field [ tagMenus::tag ]
End If
#
#Prevent the user doing anything else until
#they leave this window.
Pause/Resume Script [ Indefinitely ]
#
Exit Script [ ]
#
#
#
#END Find copyright and review it
#
#
