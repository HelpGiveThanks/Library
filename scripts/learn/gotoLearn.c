October 31, 2019 17:47:04 Library.fmp12 - gotoLearn -1-
learn: gotoLearn
#
#Basic administration tasks.
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#Clear sort so when user click's button it will
#resort records by order number.
Set Field [ TEMP::TLTestSort; "" ]
#
If [ tempSetup::kdefaultCopyright = "" ]
Show Custom Dialog [ Message: "Select the default copyright for any new records that you create by clicking the copyright button
(you can always change your mind)."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
Else If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible for creating new records) by clicking the node button.";
Default Button: “OK”, Commit: “No” ]
Halt Script
End If
#
Select Window [ Name: "Setup"; Current file ]
Set Window Title [ Current Window; New Title: "Learn" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
#
#Select the correct layout.
If [ tempSetup::layoutLmain = "" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “learn2” (testlearn) ]
Else
Go to Layout [ “learnStuff2” (testlearn) ]
End If
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
Else If [ tempSetup::layoutLmain ≠ "" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ "Learn" & Right ( tempSetup::layoutLmain ; 1 ) ]
Else
Go to Layout [ "LearnStuff" & Right ( tempSetup::layoutLmain ; 1 ) ]
End If
End If
#
#Now find and show all main learn records
#(exclude test result records which are
#also in the testlearn table).
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::orderInventoryGroupNumber; ascending
testlearn::note; ascending ]
[ Restore; No dialog ]
End If
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
#Capture keys of related tag menu items to
#to allow the citationMenu scripts to loop to the
#primary record of interest when the user navigates
#to a item on the Tag Menu window
#whose list of tags like node, keyword, test, etc.
#might contain an item related to the current
#learn record, but which one, which is why all
#the keys have to be readied. Mmm... now that
#I write this out, I'm thinking I could have the
#citationMenu scripts select the citation window
#to grab the key if any in the current current
#record that applies the the menu item.
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $$main; Value:testlearn::_Ltestlearn ]
Set Variable [ $$ref; Value:testlearn::kcreference ]
Set Variable [ $$node; Value:testlearn::kNodeOther ]
Set Variable [ $$copyright; Value:testlearn::kcopyright ]
Set Variable [ $$Key; Value:testlearn::kcKeywordOther ]
Set Variable [ $$brainstorm; Value:testlearn::kcbrainstorm ]
Set Variable [ $$test; Value:testlearn::kctestSubsectionInfo ]
Set Variable [ $$citationRecord; Value:testlearn::_Ltestlearn ]
Set Variable [ $$OtherKey; Value:testlearn::kcKeywordOther ]
Set Variable [ $$primaryNode; Value:testlearn::kNodePrimary ]
Set Variable [ $$PrimaryKey; Value:testlearn::kKeywordPrimary ]
#
#Clear module variable so test Tag Menus
#back button does not show up.
Set Variable [ $$learnRecord ]
Set Variable [ $$testTagRecord ]
#
#Note if record is locked to protect its tags.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Set Variable [ $$lockedMainLearnRecord; Value:tagTLNodePrimary::tag ]
Else
Set Variable [ $$lockedMainLearnRecord ]
End If
#
#Load keyword menu.
Set Variable [ $$stoploadCitation ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “ltagNK1” (tagMenus) ]
Perform Script [ “menuKey” ]
Else
Go to Layout [ “learnMenu3CiteS” (reference) ]
Perform Script [ “menuReference” ]
End If
#
#Return to Learn window.
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $$doNotHaltOtherScripts ]
#
#If there is only one node and it is the
#Admin node, the inform the user that they
#need to make a node for themselves.
If [ $$AdminOnlyNode = 1 and Get ( AccountName ) ≠ "Admin" ]
Show Custom Dialog [ Message: "NOTE: Log in as the Admin user if do not want to see these messages about creating a unique
node for yourself."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "Create a node/author record for yourself in the SetUp Section, so that you will have a unique
ID associated with all the records that you create."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "This is not the Setup Section."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "1) Click back until you reach the Setup Section. 2) go to the Tag Menu window. 2) Click the
node button."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "3) Click the P button next to your name to select yourself as the creator of all new library
records."; Default Button: “OK”, Commit: “Yes” ]
Else
Set Variable [ $$AdminOnlyNode ]
End If
#
