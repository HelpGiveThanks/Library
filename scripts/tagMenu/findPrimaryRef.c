July 21, 2018 14:12:45 Library.fmp12 - findPrimaryRef -1-
tagMenu: findPrimaryRef
#
#
#If this tag has a picture that is hidden, ask if
#the user wants to see the picture or find
#record's with this tag.
If [ //There is a picture to show if...
Get (LayoutName) = "ReferenceMenu3CiteNoPicture" and
(
reference::picture ≠ "" or
reference::showMedia ≠ "" and reference::URL ≠ "" or
reference::showMedia[2] ≠ "" and reference::kfileLocation ≠ "" and reference::fileName ≠ ""
)
or
Get (LayoutName) = "ReferenceMenu3CiteFindS" and
(
reference::picture ≠ "" or
reference::showMedia ≠ "" and reference::URL ≠ "" or
reference::showMedia[2] ≠ "" and reference::kfileLocation ≠ "" and reference::fileName ≠ ""
) ]
If [ reference::_Lreference = $$citationItem and $$citationMatch = "cite" ]
Show Custom Dialog [ Message: "Show this tag's picture or hide reference records tagged only with it?"; Default Button:
“hide”, Commit: “Yes”; Button 2: “show”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Show this tag's picture or find references tagged with it?"; Default Button: “find”, Commit:
“Yes”; Button 2: “show”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
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
Set Variable [ $tag; Value:tagMenus::_Ltag ]
If [ $$citationMatch = "cite" ]
Set Variable [ $tag; Value:reference::_Lreference ]
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
Set Variable [ $menu; Value:Left ( $$citationMatch ; 1 ) ]
If [ $menu = "c" and $$citationMatch = "cite" ]
Set Variable [ $menu; Value:"r" ]
Else If [ $menu = "p" and $$citationMatch = "publisher" ]
Set Variable [ $menu; Value:"x" ]
Else If [ $menu = "p" and $$citationMatch = "publication" ]
Set Variable [ $menu; Value:"y" ]
End If
#
#Get the name of the tag for error message
#at bottom of this script if needed.
Set Variable [ $name; Value:tagMenus::tag ]
If [ $$citationMatch = "cite" ]
Set Variable [ $name; Value:reference::Title ]
End If
#
#As going to the other window will be involved
#stop the record load script on that window until
#this script is finished to speed things up and
#stop flashing effect.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Go to the other window and start the find process.
Select Window [ Name: "References"; Current file ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
// Set Field [ reference::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ reference::kkeywordPrimary; $tag ]
Else If [ $menu = "n" ]
Set Field [ reference::knodePrimary; $tag ]
Else If [ $menu = "m" ]
Set Field [ reference::kmedium; $tag ]
Else If [ $menu = "c" and $$citationMatch ≠ "cite" ]
Set Field [ reference::kCopyright; $tag ]
Else If [ $menu = "p" ]
Set Field [ reference::kfolderpath; $tag ]
Else If [ $menu = "x" ]
Set Field [ reference::kpublisher; $tag ]
Else If [ $menu = "y" ]
Set Field [ reference::kpublication; $tag ]
Else If [ $menu = "r" ]
Set Field [ reference::kcitation; $tag ]
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
Set Field [ reference::kkeywordPrimary; "findNoRecords" ]
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
// Set Field [ reference::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ reference::kkeywordPrimary; $find ]
Else If [ $menu = "n" ]
Set Field [ reference::knodePrimary; $find ]
Else If [ $menu = "m" ]
Set Field [ reference::kmedium; $find ]
Else If [ $menu = "c" ]
Set Field [ reference::kCopyright; $find ]
Else If [ $menu = "p" ]
Set Field [ reference::kfolderpath; $find ]
Else If [ $menu = "x" ]
Set Field [ reference::kpublisher; $find ]
Else If [ $menu = "y" ]
Set Field [ reference::kpublication; $find ]
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
// Set Field [ reference::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ reference::kkeywordPrimary; $find ]
Else If [ $menu = "n" ]
Set Field [ reference::knodePrimary; $find ]
Else If [ $menu = "m" ]
Set Field [ reference::kmedium; $find ]
Else If [ $menu = "c" ]
Set Field [ reference::kCopyright; $find ]
Else If [ $menu = "p" ]
Set Field [ reference::kfolderpath; $find ]
Else If [ $menu = "x" ]
Set Field [ reference::kpublisher; $find ]
Else If [ $menu = "y" ]
Set Field [ reference::kpublication; $find ]
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
// Set Field [ reference::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ reference::kkeywordOther; $find ]
Else If [ $menu = "n" ]
Set Field [ reference::knodeOther; $find ]
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
// Set Field [ reference::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ reference::kkeywordOther; $find ]
Else If [ $menu = "n" ]
Set Field [ reference::knodeOther; $find ]
End If
#
#
Extend Found Set [ ]
End Loop
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
Perform Script [ “loadLearnOrRefMainRecord (update)” ]
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
Else If [ $$citationMatch = "medium" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
Else If [ $$citationMatch = "copyright" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
Else If [ $$citationMatch = "path" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
Else If [ $$citationMatch = "publication" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
Else If [ $$citationMatch = "publisher" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
Else If [ $$citationMatch = "cite" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Default Button: “OK”, Commit: “No” ]
End If
#
#
End If
