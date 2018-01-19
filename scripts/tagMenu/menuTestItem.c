January 15, 2018 16:26:20 Library.fmp12 - menuTestItem -1-
tagMenu: menuTestItem
#
#
#If there are no test subsections,
#then exit this script.
If [ TEMP::ktestSubsection = "" ]
Exit Script [ ]
Show Custom Dialog [ Message: "There are no test subsections."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#
#Close any open test item reference windows.
#NOTE: This is next loop is a work around to
#deal with the Reference window issue.
#Basically, there are several scripts that may
#open Reference windows for Info records that
#have references. Rather than try to figure out all
#the ways this occurs (easy with time), this loop
#just closes as many Reference windows as are
#currently open. Not the best solution, but it
#works and I really want to close out work on this
#4.0beta version and move on.
Loop
If [ ValueCount ( FilterValues ( WindowNames ( Get ( FileName ) ) ; "Reference" ) ) > 0 ]
Close Window [ Name: "Reference"; Current file ]
Set Variable [ $resizeTagMenusWindow; Value:1 ]
End If
Exit Loop If [ ValueCount ( FilterValues ( WindowNames ( Get ( FileName ) ) ; "Reference" ) ) = 0 ]
End Loop
#
If [ Left ( Get (LayoutName) ; 5 ) ≠ "setup" ]
If [ $$pictureWindowColor = "test" ]
Move/Resize Window [ Name: "Test"; Current file; Width: Get ( ScreenWidth ) / 2; Left: 0 ]
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get ( ScreenWidth ) / 2; Left: Get ( ScreenWidth ) / 2 ]
Else
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get (ScreenWidth) - 594; Left: 594 ]
End If
End If
Select Window [ Name: "Tag Menus"; Current file ]
#
#
#If there are information records, then set this
#variable below to inform the user of this fact
#by highlighting the info button on the
#Test Menus layout, but only if user is on the
#testInfo layout.
If [ Get(LayoutName) = "testInfo" or Get(LayoutName) = "reportTagInfo" ]
If [ Get (FoundCount) ≠ 0 ]
Set Variable [ $$thereIsInfoForThisSubsection; Value:1 ]
Else
Set Variable [ $$thereIsInfoForThisSubsection ]
End If
End If
#
#Goto correct layout, and don't load tag
#record or check spelling.
Set Variable [ $$stopTest; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenuTestItem” (tagMenus) ]
#
#If user has elected to show only the tag ...
Else If [ TEMP::DetailmoreORLessLayout = "" and Left ( Get ( LayoutName ) ; 5 ) = "setup" ]
#If subsection is locked stop its test item list
If [ $$lockedMainSubsectionRecord ≠ "" ]
Go to Layout [ “setupTestItemLOCKED” (tagMenus) ]
Else
Go to Layout [ “setupTestItem” (tagMenus) ]
End If
Else If [ TEMP::DetailmoreORLessLayout ≠ "" and Left ( Get ( LayoutName ) ; 5 ) = "setup" ]
#If subsection is locked stop its test item list
If [ $$lockedMainSubsectionRecord ≠ "" ]
Go to Layout [ “setupTestItemLOCKED” (tagMenus) ]
Else
Go to Layout [ “setupTestItem” (tagMenus) ]
End If
#
#If user has elected to show some pictures ...
Else If [ TEMP::DetailmoreORLessLayout = "" and Left ( Get ( LayoutName ) ; 4 ) = "test" ]
Go to Layout [ “testMenuTestItem” (tagMenus) ]
Else If [ TEMP::DetailmoreORLessLayout ≠ "" and Left ( Get ( LayoutName ) ; 4 ) = "test" ]
Go to Layout [ “testMenuTestItem” (tagMenus) ]
#
Else If [ Left ( Get (LayoutName) ; 6 ) = "report" ]
Go to Layout [ “reportTagItem” (tagMenus) ]
Set Variable [ $reportTestItemComment; Value:1 ]
#
End If
Set Variable [ $$citationMatch; Value:"testItem" ]
Set Field [ TEMP::mTag; TEMP::ktestSubsection ]
#
#Find test items for subsection.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenuTestItemGroup::match; TEMP::ktestItemSubsection & ¶ ]
Perform Find [ ]
#
#Don't hide FT items in template setup section.
If [ Left (Get (LayoutName) ; 5 ) ≠ "setup" ]
#
#This variable insures that if the hideFTs button
#is on, a message informing the user that this
#specific subsection's test item list has no FT
#items to show or hide will appear if the user
#clicks it and, indeed, there are no FT items
#to show.
#SO before the loop below goes looking for
#them, this variable needs to be turned on, just
#in case for the last list shown, it was turned off
#because it had FT items.
# In other words, the message is only
#turned on if there are no FT's found below, but
#before it can be turned off, we have to make
#sure it starts out being on.
Set Variable [ $$noFT_ItemsFound; Value:1 ]
#
#See if there are any FT items.
Go to Record/Request/Page
[ First ]
Loop
Go to Field [ ]
If [ tagMenus::notesOrCopyright = "FT" ]
#
#
#Turn off this variable which tells the library
#that this list has no FT items to show, because
#one was just found.
Set Variable [ $$noFT_ItemsFound ]
#
#
#If user has elected to hide form FT items, then
#omit the item from the current list.
If [ TEMP::testHideFormTextItemsFTs = 1 ]
Omit Record
#
#
#If the user wants to show FT times, then move
#on to the next item. NOTE: If the user was
#hidding them, then omiting them would move
#the script to the next item.
Else
Go to Record/Request/Page
[ Next; Exit after last ]
End If
#
#
#If this record is not an FT item, then move on
#to the next item. NOTE: If this item was an FT
#item, omitting it would advance the script
#to the next item.
Else
Go to Record/Request/Page
[ Next; Exit after last ]
End If
End Loop
End If
#
#To insure the 'sort' button will next sort
#alphabetically when clicked, note that the
#current sort is by category/group and then
#sort it by group.
Set Field [ TEMP::sortTestItem; "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuTestItemGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuTestItemGroup::name; ascending
tagMenuTestItemGroup::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
#Now go the first record and scroll
#the window to the top.
Go to Record/Request/Page
[ First ]
Set Variable [ $$stopLoadTagRecord ]
Scroll Window
[ Home ]
#
#
#Ask the user if they would like to see the
#whole test item when they click on one or not
#(they just want to go to that tag record).
If [ $$rememberTestItemChoice ≠ 1 and Get(FoundCount) ≠ 0 ]
Show Custom Dialog [ Message: "1) Enter and stay in text fields, or 2) exit them, when clicking on one to navigate to a test-item
record?"; Default Button: “exit”, Commit: “Yes”; Button 2: “enter”, Commit: “No” ]
#
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $$showAll ]
#
Else If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $$showAll; Value:1 ]
End If
#
#
#Ask if user would like their choice to be
#remembered for this session (until the library
#is restarted).
Show Custom Dialog [ Message: "Remember this enter (or exit) decision? If yes, you will not be asked again until you restart the
library."; Default Button: “Yes”, Commit: “Yes”; Button 2: “No”, Commit: “No” ]
#
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $$rememberTestItemChoice; Value:1 ]
End If
End If
#
#
#Tell the user if FT items are currently hidden,
#and then set variable so this message is not
#shown again, unless this library is restarted.
#
#Don't hide FT items in template setup section.
If [ Left (Get (LayoutName) ; 5 ) ≠ "setup" ]
If [ TEMP::testHideFormTextItemsFTs = 1 and $$showFTmessageOnlyOnce = "" and $$noFT_ItemsFound = "" ]
Set Variable [ $$showFTmessageOnlyOnce; Value:1 ]
Refresh Window
Show Custom Dialog [ Message: "NOTE: Form items (FT items) are hidden. To show them, click the hideFTs button. This
message is shown only once per session. To see it again, restart this library."; Default Button: “OK”, Commit: “Yes” ]
End If
End If
#
#
If [ Left ( Get (LayoutName) ; 6 ) ≠ "report" ]
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
#
#If in add mode, find only records tagged with
#current $$citationmatch.
If [ $$add = 1 ]
#
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to test item
tags, or keep the current records shown?"; Default Button: “keep”, Commit: “Yes”; Button 2: “show”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
#find on learn layout ...
If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "testItem" ]
Perform Find [ ]
#
#find on reference layout ...
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Enter Find Mode [ ]
Set Field [ reference::filterFind; "testItem" ]
Perform Find [ ]
End If
End If
#
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
End If
#
#Now load the tag record and turn on
#spell check script.
Set Variable [ $$stopTest ]
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord (update)” ]
#
#If on the Report item layout then tell user
#that all check items will be treated as text
#items.
If [ $reportTestItemComment = 1 and $$showReportItemCommentOnce ≠ 1 ]
Show Custom Dialog [ Message: "NOTE: All check-list items become useful as highlighted copy/paste 'T' (text) buttons in this
Report section. (This message only shows once per session. Restart the library to see it again.)"; Default Button: “OK”,
Commit: “Yes” ]
Set Variable [ $$showReportItemCommentOnce; Value:1 ]
End If
#
