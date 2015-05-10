pictures: addLinksPicturesToTagsMode
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If node is currenlty locked then stop script, inform user.
If [ nodeLockTagMenus::orderOrLock ≠ "" ]
Go to Field [ ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTagMenus::tag & " -- and enter the password to unlock it and then you will be able to add pictures and links to it."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "sample" or
nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "health" or
nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "health" or
nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "health" or
nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "health" or
nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "test" ]
Show Custom Dialog [ Message: "This record is currently locked. Select the node that created it and enter the password to unlock it, then you will able to start the delete process."; Buttons: “OK” ]
Exit Script [ ]
Else If [ tagMenus::orderOrLock ≠ "" and tagMenus::match = "health" ]
Show Custom Dialog [ Message: "This record is locked by the system."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#This script allows users to add pictures and
#file links to tags from citation records.
#
#If on the test setup layout, then stop the script
#if the user has not created any tags to add pictures
#and links to
If [ TEMP::ktest ≠ "" and Get (RecordNumber) = 0 ]
Show Custom Dialog [ Message: "Create a tag record then click the add button."; Buttons: “OK” ]
Exit Script [ ]
End If
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
Set Variable [ $$returnWIndow; Value:Get (LayoutName) ]
Set Variable [ $$returnRecord; Value:test::_Ltest ]
Else If [ Get (LastError) ≠ 112 ]
#
#If learn ...
Set Variable [ $$returnWIndow; Value:"Learn" ]
Set Variable [ $$returnLayout; Value:Get (LayoutName) ]
Set Variable [ $$returnRecord; Value:testlearn::_Ltestlearn ]
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
Go to Layout [ “ReferenceAddToTag” (reference) ]
#
// #Find all citations for current tag set.
// #( the user can always click the 'all' button to
// # to see all the records they can add to the tag
// # but I figured most of the time the user is creating
// # creating records during the add process to
// # to add to tag, and so keep the records to just
// # those created for a type of tag would be easier
// # on the user. )
// Set Error Capture [ On ]
// Allow User Abort [ Off ]
// Enter Find Mode [ ]
// Set Field [ reference::kcsection; TEMP::ksection ]
// #
// #If the citationMatch equal "key" then substitute
// #"keyword" for "key" as on the layout it makes
// #more sense to have the user check a keyword
// #checkbox item than a key item as key is short
// #for keyword in this case.
May 10, 平成27 11:19:45 Library.fp7 - addLinksPicturesToTagsMode -1-
pictures: addLinksPicturesToTagsMode
// #( You can see these checkboxes at the bottom
// # of every Reference record )
// If [ $$citationMatch = "key" ]
// Set Field [ reference::filterFind; "*" & "keyword" ]
// #
// #If the citationMatch equals any other tag type ...
// Else If [ $$citationMatch
≠ "key" ]
// Set Field [ reference::filterFind; "*" & Quote ( $$citationMatch ) ]
// End If
// #
// Perform Find [ ] #
#Clear the stop load record variable and load
#the current record's info.
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ] #
#Go to tag menu window.
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ] #
#END start add mode ####
#BEGIN stop add mode #
#If in add mode then clear the add variable to conditionally
#format the 'add' button to indicate that add mode
#has been turned off.
Else If [ $$add = 1 ]
Set Variable [ $$add ] #
#If the user was in test mode prior to add mode ...
If [ $$citationMatch = "testItem" ] #
#This may be lazy, but instead of doing an if
#test to figure out what window a user is in,
#it seems that telling the system to select both
#possible windows the user could be
#in works just fine. The system always
#selects the one the user is in.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ] #
#Now loop to the record the user was on,
#and turn off the load record script to speed things
#up. ( This record set does not need to be found
# first because during add mode test records
# are not touched. )
Set Variable [ $$ID; Value:"ignore" ]
Go to Layout [ “testSetup” (test) ]
Loop
Exit Loop If [ test::_Ltest = $$returnRecord ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop #
#Set the window title to Setup and turn back on
#the load record script, but do not load the record
#as this record's variables are already loaded.
Set Window Title [ Current Window; New Title: "Setup" ]
Set Variable [ $$ID; Value:test::_Ltest ] #
#Go to the tag menu and perform the TestItem
#menu script to reset the conditional formatting.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “setupTestItem” (tagMenus) ]
Perform Script [ “menuTestItem” ] #
#Clear all add mode variables and exit script.
Set Variable [ $$returnWindow ]
Set Variable [ $$returnLayout ]
Set Variable [ $$returnRecord ]
Set Variable [ $$tagLayout ]
Exit Script [ ] #
#If the user was in default mode prior to add mode ...
Else If [ $$returnWindow = "defaultSetup" ] #
#This may be lazy, but instead of doing an if
#test to figure out what window a user is in,
#it seems that telling the system to select both
#possible windows the user could be
#in works just fine. The system always
#selects the one the user is in.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ] #
#There is always only one default record, so
#finding and looping to record is not necessary.
Go to Layout [ “defaultSetup” (tempSetup) ]
Set Window Title [ Current Window; New Title: "Setup" ] #
#Go to the tag menu and perform the Node
#menu script to reset the conditional formatting.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “defaultNode1” (tagMenus) ]
Perform Script [ “defaultNodeMenu” ] #
#Clear all add mode variables and exit script.
Set Variable [ $$returnWindow ]
Set Variable [ $$returnLayout ]
Set Variable [ $$returnRecord ]
Set Variable [ $$tagLayout ]
Exit Script [ ]
End If #
#If going back to a Learn or Reference layout,
#then first turn off the record load variable.
#I decided to do it here rather than include it
#each time before it is needed.
Set Variable [ $$stoploadCitation; Value:1 ] #
#If the user was in learn mode prior to add mode ...
If [ $$returnWindow = "Learn" ]
May 10, 平成27 11:19:45 Library.fp7 - addLinksPicturesToTagsMode -2-
pictures: addLinksPicturesToTagsMode #
#Go to tag layout user was on before entering
#add mode. ( This may not be useful as user
# could also predict that tag window will stay
# on the tag it is on in add mode. User might
# not remember what tag they where on when
# they started add mode. Have to see if this
# is useful or not. )
Select Window [ Name: "Tag Menus"; Current file ] #
If [ $$citationMatch = "node" or
$$citationMatch = "key" or
$$citationMatch = "testItem" ]
Go to Layout [ $$tagLayout ] #
Else If [ $$citationMatch = "medium" or
$$citationMatch = "health" or
$$citationMatch = "organ" or
$$citationMatch = "copyist" or
//$$citationMatch = "sample" or
$$citationMatch = "path" ]
Go to Layout [ $$tagLayout ]
End If #
#This may be lazy, but instead of doing an if
#test to figure out what window a user is in,
#it seems that telling the system to select both
#possible windows the user could be
#in works just fine. The system always
#selects the one the user is in.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
Set Window Title [ Current Window; New Title: "Learn" ]
Go to Layout [ $$returnLayout ] #
#Find main learn records.
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
// Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ] #
#Go to record user was on before add mode.
Sort Records [ Specified Sort Order: testlearn::date; descending
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
End Loop #
#Clear all add mode variables and exit script.
Set Variable [ $$returnWindow ]
Set Variable [ $$returnLayout ]
Set Variable [ $$returnRecord ]
Set Variable [ $$tagLayout ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ] #
#If the user was in reference mode prior to add mode ...
Else If [ $$returnWIndow = "References" ] #
#Go to tag layout user was on before entering
#add mode. ( This may not be useful as user
# could also predict that tag window will stay
# on the tag it is on in add mode. User might
# not remember what tag they where on when
# they started add mode. Have to see if this
# is useful or not. )
Select Window [ Name: "Tag Menus"; Current file ] #
#Get the record number.
Set Variable [ $recordNumber; Value:Get (RecordNumber) ] #
If [ $$citationMatch = "node" or
$$citationMatch = "key" or
$$citationMatch = "testItem" ]
Go to Layout [ Middle ( TEMP::layoutRtagK ; 5 ; 42 ) ] #
Else If [ $$citationMatch = "medium" or
$$citationMatch = "organ" or
$$citationMatch = "copyist" or
$$citationMatch = "path" ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ] #
Else If [ $$citationMatch = "health" ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
End If #
#This may be lazy, but instead of doing an if
#test to figure out what window a user is in,
#it seems that telling the system to select both
#possible windows the user could be
#in works just fine. The system always
#selects the one the user is in.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
Set Window Title [ Current Window; New Title: "References" ]
If [ TEMP::InventoryLibaryYN
≠ "" ]
Go to Layout [ “ReferenceStuff” (reference) ]
Else
Go to Layout [ “Reference” (reference) ]
End If #
#Find main reference records.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
// Set Field [ reference::filterFind; "main" ]
Perform Find [ ] #
#Go to record user was on before add mode.
Sort Records [ Specified Sort Order: tagKeywordPrimary::tag; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
May 10, 平成27 11:19:45 Library.fp7 - addLinksPicturesToTagsMode -3-
pictures: addLinksPicturesToTagsMode
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
Perform Script [ “loadCitation” ]
#
#Go to record user was on before add mode.
Scroll Window
[ Home ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
#
#
End If
End If
May 10, 平成27 11:19:45 Library.fp7 - addLinksPicturesToTagsMode -4-
