July 20, 2018 21:31:03 Library.fmp12 - addLinksPicturesToTagsMode -1-
pictures: addLinksPicturesToTagsMode
#
#For now, hide the the add button until a
#solution can be figured out to allow user to
#create references for pictures used by node
#tags in inventory mode.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Show Custom Dialog [ Message: "In inventory mode, pictures and links cannot be added to tags as of library version 4.0d. Plans
are to add this feature back in a future version."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Stop user from adding pictures from
#brainstorm menu, and tell user how.
If [ $$citationMatch = "brainstorm" ]
Go to Field [ ]
Show Custom Dialog [ Message: "To add or edit a picture or website link 1) go to the copyright tag menu in the Setup or
Reference section, 2) select this copyright, 3) click review, 4) click add."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If user is editing a reference record then stop
#this script and inform user as to why.
If [ $$stopAdd = 1 ]
Go to Field [ ]
Show Custom Dialog [ Message: "Exit 'edit' mode to add pictures to tags: 1) click 'back' in the Reference window, then 2) click
'add' in the Tag Menus window. "; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If the user has not selected a primary node,
#then prevent this script from creating new .
#records. All records must be created by the
#primary node.
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window OR create a node record for
yourself?"; Default Button: “select”, Commit: “No”; Button 2: “create”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Halt Script
Else
Set Field [ tempSetup::kdefaultNodePrimary; "self" ]
End If
End If
#
#If node is currenlty locked then stop script, inform user.
If [ tagCreatorLock::orderOrLock ≠ "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & tagCreatorLock::tag & " — and enter
the password to unlock it; you will then be able to add pictures and links to it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
If [ tagCreatorLock::orderOrLock ≠ "" and tagMenus::match = "brainstorm" or
tagCreatorLock::orderOrLock ≠ "" and tagMenus::match = "copyright" or
tagCreatorLock::orderOrLock ≠ "" and tagMenus::match = "test" ]
Show Custom Dialog [ Message: "This record is currently locked. Select the node that created it and enter the password to
unlock it, then you will able to start the delete process."; Default Button: “OK”, Commit: “No” ]
Exit Script [ ]
Else If [ tagMenus::orderOrLock ≠ "" and tagMenus::match = "copyright" ]
Show Custom Dialog [ Message: "This record is a default copyright tag and so is locked. Choose reference-section images and
web links for any copyright tags that you create: 1) Click 'new' and then 2) click 'add'."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#This script allows users to add pictures and
#file links to tags from citation records.
#
#If on the test setup layout, then stop the script
#if the user has not created any tags to add pictures
#and links to
If [ TEMP::ktestSubsection ≠ "" and Get (RecordNumber) = 0 ]
Show Custom Dialog [ Message: "Create a tag record then click the add button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If user is in the copyright window then
#temporarily close this window and them
#re-open it at the end of the add pictures
#process.
If [ Get (WindowName) = "Copyright" ]
Set Variable [ $$userInCopyrightWindow; Value:1 ]
Close Window [ Current Window ]
End If
#
#
#Prevent halting in loadTagRecord script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
#
#
#If user is not in add mode (indicated green highlight
#on 'add' button) then enter add mode.
#Go to layout where user can see all
#possible places an item can be added:
#3 picture places and 3 link places.
If [ $$add = "" ]
#
#if user was on the keyword or nod tag layout ...
If [ $$citationMatch = "key" or
$$citationMatch = "node" ]
#
#Remember layout user was on.
Set Variable [ $$tagLayout; Value:Get (LayoutName) ]
Go to Layout [ “addMenuNodeKeyword” (tagMenus) ]
#
#if user was on the testItem tag layout ...
Else If [ $$citationMatch = "testItem" ]
#
#Remember layout user was on.
Set Variable [ $$tagLayout; Value:Get (LayoutName) ]
Go to Layout [ “addMenuTestItem” (tagMenus) ]
#
#if user was any of the other tag layouts ...
Else If [ 1 = 1 ]
#
#Remember layout user was on.
Set Variable [ $$tagLayout; Value:Get (LayoutName) ]
Go to Layout [ “addMenu1” (tagMenus) ]
End If
#
#Conditionally format add button.
Set Variable [ $$add; Value:1 ]
Refresh Window
#
#Capture main window layout.
#Capture record user is on.
#Stop record load script to speed things up.
Set Variable [ $$stoploadCitation; Value:1 ]
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
#
#If setup ...
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$returnWIndow; Value:"defaultSetup" ]
Set Variable [ $$returnRecord; Value:testSubsectionTemplate::_LtestSubsection ]
Else If [ Get (LastError) ≠ 112 ]
#
#If learn ...
Set Variable [ $$returnWIndow; Value:"Learn" ]
Set Variable [ $$returnLayout; Value:Get (LayoutName) ]
Set Variable [ $$returnRecord; Value:testlearn::_Ltestlearn ]
#
#If adding to copyright records then show
#locked reference copyright pictures.
If [ $$citationMatch = "copyright" ]
Extend Found Set [ Specified Find Requests: Find Records; Criteria: reference::lock: “"lock"” ]
[ Restore ]
#
#Explalin to user what these additional
Show Custom Dialog [ Message: "Default, locked copyright record images and links are shown (scroll down) in
case they will be useful to you. Create new copyright reference records for links and images as needed (you'll
need to exit add mode first)."; Default Button: “OK”, Commit: “No” ]
End If
End If
Else If [ Get (LastError) ≠ 112 ]
#
#If references ...
Set Variable [ $$returnWIndow; Value:"References" ]
Set Variable [ $$returnRecord; Value:reference::_Lreference ]
End If
#
#Re-title main window.
Set Window Title [ Current Window; New Title: "References" ]
#
#Goto the referenceTag layout.
If [ $$userInCopyrightWindow = "" ]
Go to Layout [ “ReferenceAddToTag” (reference) ]
Else
Go to Layout [ “ReferenceAddToCopyright” (reference) ]
End If
#
#Omit locked records, which are the copyright
#images used by default copyright tags.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
#
#If no records are showing then, show all Reference records.
If [ Get (FoundCount) = 0 ]
#
#Find main records.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Show All Records
#
#Omit locked records, which are the copyright
#images used by default copyright tags.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
#
End If
#
#If adding to copyright records then show
#locked reference copyright pictures.
If [ $$citationMatch = "copyright" ]
Extend Found Set [ Specified Find Requests: Find Records; Criteria: reference::lock: “"lock"” ]
[ Restore ]
#
#Remove all records that lack both pictures and
#links, as these are the only things users can
#add to copyright records.
Go to Record/Request/Page
[ First ]
Loop
If [ reference::picture = "" and reference::URL = "" ]
Omit Record
Set Variable [ $omitRecordsWithoutPicturesOrLinks; Value:1 ]
Else
Go to Record/Request/Page
[ Next ]
End If
Exit Loop If [ Get ( FoundCount ) = Get ( RecordNumber ) ]
End Loop
#
Go to Record/Request/Page
[ First ]
#
#If references were moved then inform
#user of this and why.
If [ $omitRecordsWithoutPicturesOrLinks ≠ "" ]
Show Custom Dialog [ Message: "References have been removed that have no picture or link. The copyright image
field requires the image to be stored in the references picture field."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#Explalin to user what these additional
Show Custom Dialog [ Message: "Locked copyright records' images and links are shown (scroll down) in case they will be
useful to you. Create new copyright reference records for links and images as needed (you'll need to exit add mode
first)."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#Clear the stop load record variable and load
#the current record's info.
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord (update)” ]
#
#Go to tag menu window.
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
#
#END start add mode
#
#
#
#
#BEGIN stop add mode
#
#If in add mode then clear the add variable to conditionally
#format the 'add' button to indicate that add mode
#has been turned off.
Else If [ $$add = 1 ]
Set Variable [ $$add ]
#
#If the user was in test mode prior to add mode ...
If [ $$citationMatch = "testItem" ]
#
#This may be lazy, but instead of doing an if
#test to figure out what window a user is in,
#it seems that telling the system to select both
#possible windows the user could be
#in works just fine. The system always
#selects the one the user is in.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
#
#Now loop to the record the user was on,
#and turn off the load record script to speed things
#up. ( This record set does not need to be found
# first because during add mode test records
# are not touched. )
Set Variable [ $$ID; Value:"ignore" ]
Go to Layout [ “setupTestSubsection” (testSubsectionTemplate) ]
Loop
Exit Loop If [ testSubsectionTemplate::_LtestSubsection = $$returnRecord ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Set the window title to Setup and turn back on
#the load record script, but do not load the record
#as this record's variables are already loaded.
Set Window Title [ Current Window; New Title: "Setup" ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
#
#Go to the tag menu and perform the TestItem
#menu script to reset the conditional formatting.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “setupTestItem” (tagMenus) ]
Perform Script [ “menuTestItem” ]
#
#Clear all add mode variables and exit script.
Set Variable [ $$returnWindow ]
Set Variable [ $$returnLayout ]
Set Variable [ $$returnRecord ]
Set Variable [ $$tagLayout ]
Exit Script [ ]
#
#If the user was in default mode prior to add mode ...
Else If [ $$returnWindow = "defaultSetup" ]
#
#If adding to copyright records then remove/omit
#locked reference copyright pictures.
Select Window [ Name: "References"; Current file ]
If [ $$citationMatch = "copyright" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
Set Variable [ $$stoploadCitation ]
End If
#
#There is always only one default record, so
#finding and looping to record is not necessary.
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
Set Window Title [ Current Window; New Title: "Setup" ]
#
#Go to the tag menu and perform the Node
#menu script to reset the conditional formatting.
Select Window [ Name: "Tag Menus"; Current file ]
#
#If user was in the copyright window then
If [ $$citationMatch = "copyright" ]
Go to Layout [ “defaultCopyright” (tagMenus) ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationitem; Value:tempSetup::kdefaultCopyright ]
Refresh Window
If [ $$userInCopyrightWindow = 1 ]
Perform Script [ “reviewCopyright (update)” ]
#
#
#Turn back on the last section of the
#loadTagRecord script, which was turned on
#when this add script started add mode.
Set Variable [ $$doNotHaltOtherScripts ]
#
#Exit the script after running the above script as the
#variables below are cleared in the above script.
Exit Script [ ]
End If
Else
Go to Layout [ “defaultNode2” (tagMenus) ]
Perform Script [ “defaultNodeMenu” ]
End If
#
#Turn back on the last section of the
#loadTagRecord script, which was turned on
#when this add script started add mode.
Set Variable [ $$doNotHaltOtherScripts ]
#
#Clear all add mode variables and exit script.
Set Variable [ $$returnWindow ]
Set Variable [ $$returnLayout ]
Set Variable [ $$returnRecord ]
Set Variable [ $$tagLayout ]
Exit Script [ ]
End If
#
#If going back to a Learn or Reference layout,
#then first turn off the record load variable.
#I decided to do it here rather than include it
#each time before it is needed.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#If the user was in learn mode prior to add mode ...
If [ $$returnWindow = "Learn" ]
#
#Go to tag layout user was on before entering
#add mode. ( This may not be useful as user
# could also predict that tag window will stay
# on the tag it is on in add mode. User might
# not remember what tag they where on when
# they started add mode. Have to see if this
# is useful or not. )
Select Window [ Name: "Tag Menus"; Current file ]
#
If [ $$citationMatch = "node" or
$$citationMatch = "key" or
$$citationMatch = "testItem" ]
#
Go to Layout [ $$tagLayout ]
#
Else If [ $$citationMatch = "medium" or
$$citationMatch = "copyright" or
$$citationMatch = "publication" or
$$citationMatch = "publisher" or
//$$citationMatch = "brainstorm" or
$$citationMatch = "path" ]
Go to Layout [ $$tagLayout ]
End If
#
#
#This may be lazy, but instead of doing an if
#test to figure out what window a user is in,
#it seems that telling the system to select both
#possible windows the user could be
#in works just fine. The system always
#selects the one the user is in.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
Set Window Title [ Current Window; New Title: "Learn" ]
Go to Layout [ $$returnLayout ]
#
// #Find main learn records.
// Enter Find Mode [ ]
// Set Field [ testlearn::filterFind; "main" & ¶ ]
// Perform Find [ ]
#
#Go to record user was on before add mode.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$returnRecord ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Clear all add mode variables and exit script.
Set Variable [ $$returnWindow ]
Set Variable [ $$returnLayout ]
Set Variable [ $$returnRecord ]
Set Variable [ $$tagLayout ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord (update)” ]
#
#If the user was in reference mode prior to add mode ...
Else If [ $$returnWIndow = "References" ]
#
#Go to tag layout user was on before entering
#add mode. ( This may not be useful as user
# could also predict that tag window will stay
# on the tag it is on in add mode. User might
# not remember what tag they where on when
# they started add mode. Have to see if this
# is useful or not. )
Select Window [ Name: "Tag Menus"; Current file ]
#
#Get the record number.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
If [ $$citationMatch = "node" or
$$citationMatch = "key" or
$$citationMatch = "testItem" ]
#
Go to Layout [ Middle ( TEMP::layoutRtagK ; 5 ; 42 ) ]
#
Else If [ $$citationMatch = "medium" or
$$citationMatch = "publication" or
$$citationMatch = "publisher" or
$$citationMatch = "path" ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
#
Else If [ $$citationMatch = "copyright" ]
Go to Layout [ “ReferenceMenuCopyright” (tagMenus) ]
End If
#
#This may be lazy, but instead of doing an if
#test to figure out what window a user is in,
#it seems that telling the system to select both
#possible windows the user could be
#in works just fine. The system always
#selects the one the user is in.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
Set Window Title [ Current Window; New Title: "References" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ReferenceStuff” (reference) ]
Else
Go to Layout [ “Reference” (reference) ]
End If
#
#If adding to copyright records then remove/omit
#locked reference copyright pictures.
Select Window [ Name: "References"; Current file ]
If [ $$citationMatch = "copyright" ]
Set Variable [ $$stoploadCitation; Value:1 ]
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
Set Variable [ $$stoploadCitation ]
End If
#
#Keep the reference records the user found
#instead of finding all the Reference records
#when the user leaves add mode.
// #Find main reference records.
// Set Error Capture [ On ]
// Allow User Abort [ Off ]
// Enter Find Mode [ ]
// Set Field [ reference::filterFind; "main" ]
// Perform Find [ ]
#
#Go to record user was on before add mode.
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::tag; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Loop
Exit Loop If [ reference::_Lreference = $$returnRecord ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Clear all add mode variables and exit script.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$returnLayout ]
Set Variable [ $$returnRecord ]
Set Variable [ $$returnWindow ]
Perform Script [ “loadLearnOrRefMainRecord (update)” ]
#
#Go to record user was on before add mode.
Scroll Window
[ Home ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
#
#If user was in the copyright window then
#return user to this window.
If [ $$userInCopyrightWindow = 1 ]
Set Variable [ $$userInCopyrightWindow ]
Perform Script [ “reviewCopyright (update)” ]
End If
#
End If
End If
#
#Turn back on the last section of the
#loadTagRecord script, which was turned on
#when this add script started add mode.
Set Variable [ $$doNotHaltOtherScripts ]
#
#
#Go to tag menu window.
Select Window [ Name: "Tag Menus"; Current file ]
#
#
