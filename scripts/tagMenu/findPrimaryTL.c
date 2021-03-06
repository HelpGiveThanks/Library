July 21, 2018 14:13:09 Library.fmp12 - findPrimaryTL -1-
tagMenu: findPrimaryTL
#
#
#If this tag has a picture that is hidden, ask if
#the user wants to see the picture or find
#record's with this tag.
If [ //There is a picture to show if...
Get (LayoutName) = "learnMenu4NoPicRefCiteFindTL" and
(
testlearn::picture ≠ "" or
testlearn::kshowReferencedMedia ≠ ""
)
or
Get (LayoutName) = "learnFindCiteS" and
(
reference::picture ≠ "" or
reference::showMedia ≠ "" and reference::URL ≠ "" or
reference::showMedia[2] ≠ "" and reference::kfileLocation ≠ "" and reference::fileName ≠ ""
) ]
If [ "L"& testlearn::_Ltestlearn & ¶ = FilterValues ( $$Found ; "L" & testlearn::_Ltestlearn )
or
"r" & reference::_Lreference & ¶ = FilterValues ( $$Found ; "r" & reference::_Lreference ) ]
Show Custom Dialog [ Message: "Show this tag's picture or hide learn records tagged only this tag?"; Default Button: “hide”,
Commit: “Yes”; Button 2: “show”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Show this tag's picture or find learn records tagged with it?"; Default Button: “find”,
Commit: “Yes”; Button 2: “show”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
End If
If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $$stopOpenNewTextWindow ]
Perform Script [ “showCitationPicture1inNewWindow (udpate)” ]
Exit Script [ ]
End If
If [ Get (LastMessageChoice) = 3 ]
Exit Script [ ]
End If
End If
#
#
#Select tag to be found.
If [ Right ( Get (LayoutName) ; 4 ) = "cite"
or
Right ( Get (LayoutName) ; 5 ) = "citeS" ]
Set Variable [ $tag; Value:reference::_Lreference ]
Else If [ Right ( Get (LayoutName) ; 4 ) = "find" or Get (LayoutTableName) = "tagMenus" ]
Set Variable [ $tag; Value:tagMenus::_Ltag ]
Else If [ Right ( Get (LayoutName) ; 4 ) = "test" ]
Set Variable [ $tag; Value:testSubsectionTemplate::_LtestSubsection ]
Else If [ Right ( Get (LayoutName) ; 2 ) = "tl" ]
Set Variable [ $tag; Value:testlearn::_Ltestlearn ]
#
#After finding learn records tagged with this
#learn record, find this learn record too so user
#can see full context of linked/tagged
#records/thoughts/notes/etc..
Set Variable [ $findSelfAlso; Value:testlearn::_Ltestlearn ]
End If
#
#Select the kind of tag to be found. We grab
#only the first three letters because the shortest
#menu item 'key' has only three letters, and because
#we need the same number of characters/letters
#to make up this variable so when it is added to
#the first part of an item in the found list below
#it can be removed by the system which only
#can be told how many characters to remove.
#This variable is thus a meta tag added to an
#ID number to tell the system from which menu
#did this item come. This meta tag or tag allows
#us to make a list of ID numbers from various
#tag menus: key, node, medium, etc.
If [ $findSelfAlso = "" ]
Set Variable [ $menu; Value:Left ( $$citationMatch ; 1 ) ]
Else
Set Variable [ $menu; Value:"L" ]
End If
#
#Get the name of the tag for error message
#at bottom of this script if needed.
If [ Right ( Get (LayoutName) ; 4 ) = "cite" ]
Set Variable [ $name; Value:reference::referenceShort ]
Else If [ Right ( Get (LayoutName) ; 4 ) = "find" or Get (LayoutTableName) = "tagMenus" ]
Set Variable [ $name; Value:tagMenus::tag ]
Else If [ Right ( Get (LayoutName) ; 4 ) = "test" ]
Set Variable [ $name; Value:testSubsectionTemplate::name ]
Else If [ Right ( Get (LayoutName) ; 2 ) = "tl" ]
Set Variable [ $name; Value:testlearn::note ]
End If
#
#As going to the other window will be involved
#stop the record load script on that window until
#this script is finished to speed things up and
#stop flashing effect.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Go to the other window and start the find process.
Select Window [ Name: "Learn"; Current file ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
// Set Field [ testlearn::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ testlearn::kKeywordPrimary; $tag ]
Else If [ $menu = "n" ]
Set Field [ testlearn::kNodePrimary; $tag ]
Else If [ $menu = "r" or $menu = "L" ]
Set Field [ testlearn::kcreference; $tag ]
Else If [ $menu = "t" ]
Set Field [ testlearn::kctestSubsectionInfo; "*" & $tag & ¶ ]
Else If [ $menu = "b" ]
Set Field [ testlearn::kcbrainstorm; "*" & $tag & ¶ ]
End If
#
#
#If this is the first find, note this and perform
#the find.
If [ $$firstFind = "" ]
Set Variable [ $$firstFind; Value:1 ]
Set Variable [ $$found; Value:$menu & $tag & ¶ ]
Perform Find [ ]
#
#If nothing was found capture the error message
#as steps before showing the error message will
#delete it from the system and we need it to
#activate the error message below if there was
#an error.
Set Variable [ $error; Value:Get (LastError) ]
#
#If this is not the first find and the item that
#the user clicked on to start this script has
#not already been found, then add items tagged
#with it to the current set of found records.
Else If [ $$firstFind = 1 ]
If [ $menu & $tag & ¶ ≠ FilterValues ( $$found ; $menu & $tag) ]
Extend Found Set [ ]
#
#If nothing was found capture the error message
#as steps before showing the error message will
#delete it from the system and we need it to
#activate the error message below if there was
#an error.
Set Variable [ $error; Value:Get (LastError) ]
#
#Add the tag from the list of found tagged records.
Set Variable [ $found; Value:$$found ]
Set Variable [ $$found; Value:$menu & $tag & ¶ & $found ]
#
#If this is not the first find and the item that
#the user clicked on to start this script has
#already been found, then remove tag from the
#the list of found tagged records.
Else If [ $menu & $tag & ¶= FilterValues ( $$found ; $menu & $tag & ¶) ]
Set Variable [ $found; Value:$$found ]
Set Variable [ $$found; Value:Substitute ( $found ; $menu & $tag & ¶ ; "" ) ]
#
#Enter browse mode to clear the find selections
#set at the beginning of this script.
Enter Browse Mode
#
#If after removing this item from the list of found
#tagged records the list is empty, perform a find
#that will result in zero records being found
#to reflect the fact that the user currently has
#an empty found list.
If [ $$found = "" ]
Set Variable [ $$firstFind ]
Enter Find Mode [ ]
#
#
#Since ID numbers are numbers, the text
#'findnoRecords' entered in the ID field will result
#in zero records being found.
Set Field [ testlearn::kKeywordPrimary; "findNoRecords" ]
#
#
Perform Find [ ]
#
#If after removing this item from the $$found list,
#the list is not empty, refind all records still on
#the list one tag at a time.
Else If [ $$found ≠ "" ]
#
#Create a copy of the found list. Items will be
#removed from this one at a time as they are found.
Set Variable [ $findList; Value:$$found ]
#
#Get the menu item name so system will know
#what field to put the ID number into to find
#records tagged with this item.
Set Variable [ $menu; Value:Left ( ( GetValue ( $findList ; 1 ) ) ; 1 ) ]
#
#Get the ID number of the tag to be found.
#(the number 42 is a joke, essentially the number
#needs to be big enough to capture the full ID number
#which is much shorter, but overkill doesn't hurt)
#FYI: joke is from Hitchhiker's Guide to the Galaxy
Set Variable [ $find; Value:Middle ( ( GetValue ( $findList ; 1 ) ) ; 2 ; 42 ) ]
#
#Remove it from the list of tags to be found.
Set Variable [ $subtract; Value:$findList ]
Set Variable [ $findList; Value:Substitute ( $subtract ; $menu & $find & ¶ ; "" ) ]
#
#Find main window records tagged with it.
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ testlearn::kKeywordPrimary; $find ]
Else If [ $menu = "n" ]
Set Field [ testlearn::kNodePrimary; $find ]
Else If [ $menu = "r" or $menu = "L" ]
Set Field [ testlearn::kcreference; $find ]
Else If [ $menu = "t" ]
Set Field [ testlearn::kctestSubsectionInfo; "*" & $find & ¶ ]
Else If [ $menu = "b" ]
Set Field [ testlearn::kcbrainstorm; "*" & $find & ¶ ]
End If
#
#
#If there is more than one item on the $$found
#list, then find the rest of records tagged with
#this items/tags.
Perform Find [ ]
Loop
#
#When the list is empty stop finding stuff.
Exit Loop If [ ValueCount ( $findList ) = 0 ]
#
#Get the menu item name so system will know
#what field to put the ID number into to find
#records tagged with this item.
Set Variable [ $menu; Value:Left ( ( GetValue ( $findList ; 1 ) ) ; 1 ) ]
#
#Get the ID number of the tag to be found.
Set Variable [ $find; Value:Middle ( ( GetValue ( $findList ; 1 ) ) ; 2 ; 42 ) ]
#
#Remove it from the list of tags to be found.
Set Variable [ $subtract; Value:$findList ]
Set Variable [ $findList; Value:Substitute ( $subtract ; $menu & $find & ¶ ; "" ) ]
#
#Find main window records tagged with it.
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ testlearn::kKeywordPrimary; $find ]
Else If [ $menu = "n" ]
Set Field [ testlearn::kNodePrimary; $find ]
Else If [ $menu = "r" or $menu = "L" ]
Set Field [ testlearn::kcreference; $find ]
Else If [ $menu = "t" ]
Set Field [ testlearn::ktestSubsection; $find ]
Else If [ $menu = "b" ]
Set Field [ testlearn::kcbrainstorm; $find ]
End If
#
#
Extend Found Set [ ]
End Loop
End If
End If
End If
#
#Refind any Other Keyword items.
If [ $$foundOther ≠ "" ]
#
#Create a copy of the found list. Items will be
#removed from this one at a time as they are found.
Set Variable [ $findList; Value:$$foundOther ]
#
#Get the menu item name so system will know
#what field to put the ID number into to find
#records tagged with this item.
Set Variable [ $menu; Value:Left ( ( GetValue ( $findList ; 1 ) ) ; 1 ) ]
#
#Get the ID number of the tag to be found.
Set Variable [ $find; Value:Middle ( ( GetValue ( $findList ; 1 ) ) ; 2 ; 42 ) ]
#
#Remove it from the list of tags to be found.
Set Variable [ $subtract; Value:$findList ]
Set Variable [ $findList; Value:Substitute ( $subtract ; $menu & $find & ¶ ; "" ) ]
#
#Find main window records tagged with it.
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ testlearn::kcKeywordOther; $find ]
Else If [ $menu = "n" ]
Set Field [ testlearn::kNodeOther; $find ]
End If
#
#
Extend Found Set [ ]
#
#If there is more than one item on the $$foundOther
#list, then find the rest of records tagged with
#this items/tags.
Loop
#
#When the list is empty stop finding stuff.
Exit Loop If [ ValueCount ( $findList ) = 0 ]
#
#Get the menu item name so system will know
#what field to put the ID number into to find
#records tagged with this item.
Set Variable [ $menu; Value:Left ( ( GetValue ( $findList ; 1 ) ) ; 1 ) ]
#
#Get the ID number of the tag to be found.
Set Variable [ $find; Value:Middle ( ( GetValue ( $findList ; 1 ) ) ; 2 ; 42 ) ]
#
#Remove it from the list of tags to be found.
Set Variable [ $subtract; Value:$findList ]
Set Variable [ $findList; Value:Substitute ( $subtract ; $menu & $find & ¶ ; "" ) ]
#
#Find main window records tagged with it.
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ testlearn::kcKeywordOther; $find ]
Else If [ $menu = "n" ]
Set Field [ testlearn::kNodeOther; $find ]
End If
#
#
Extend Found Set [ ]
End Loop
End If
#
#After finding learn records tagged with this
#learn record, find this learn record too so user
#can see full context of linked/tagged
#records/thoughts/notes/etc..
If [ TEMP::InventoryLibraryYN = "" and $error = 0 ]
If [ Filter ( $$found ; "L" ) = "L" ]
#
#Create a copy of the found list. Items will be
#removed from this one at a time as they are found.
Set Variable [ $LearnTagList; Value:$$found ]
Loop
#
#Get the menu item name so system will know
#what field to put the ID number into to find
#records tagged with this item.
Set Variable [ $menu; Value:Left ( ( GetValue ( $LearnTagList ; 1 ) ) ; 1 ) ]
#
#Get the ID number of the tag to be found.
#(the number 42 is a joke, essentially the number
#needs to be big enough to capture the full ID number
#which is much shorter, but overkill doesn't hurt)
#FYI: joke is from Hitchhiker's Guide to the Galaxy
Set Variable [ $find; Value:Middle ( ( GetValue ( $LearnTagList ; 1 ) ) ; 2 ; 42 ) ]
#
#Remove it from the list of tags to be found.
Set Variable [ $subtract; Value:$LearnTagList ]
Set Variable [ $LearnTagList; Value:Substitute ( $subtract ; $menu & $find & ¶ ; "" ) ]
#
If [ $menu = "L" ]
Enter Find Mode [ ]
Set Field [ testlearn::_Ltestlearn; $find ]
Extend Found Set [ ]
End If
#
#When the list is empty stop finding stuff.
Exit Loop If [ ValueCount ( $LearnTagList ) = 0 ]
#
End Loop
End If
End If
#
#Sort according to current sort in Main window.
Sort Records [ ]
[ No dialog ]
#
#Go to first record and preform record load script.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord” ]
#
#Return to Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
#
#If no records where found tell user why and
#remove tag ID from list of tags attached to records
#in the main window.
If [ $error = 401 ]
If [ $$firstFind = "" ]
Set Variable [ $$found ]
Else If [ $$firstFind ≠ "" ]
Set Variable [ $$found; Value:Substitute ( $found ; $menu & $tag & ¶ ; "" ) ]
End If
Refresh Window
#
#
If [ $$citationMatch = "key" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use as a primary keyword."; Default Button: “OK”, Commit:
“No” ]
Else If [ $$citationMatch = "node" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use as a primary node."; Default Button: “OK”, Commit: “No” ]
Else If [ $$citationMatch = "ref" ]
Show Custom Dialog [ Message: "'" & Left ( $name ; 65 ) & "..." & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
Else If [ $$citationMatch = "learn" ]
Show Custom Dialog [ Message: "'" & Left ( $name ; 65 ) & "..." & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
Else If [ $$citationMatch = "test" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
Else If [ $$citationMatch = "brainstorm" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
End If
#
#
End If
