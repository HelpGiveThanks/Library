tagMenu: findPrimaryRef
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
End If
#
#Get the name of the tag for error message
#at bottom of this script if needed.
Set Variable [ $name; Value:tagMenus::tag ]
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
Set Field [ reference::kcsection; TEMP::ksection ]
// Set Field [ reference::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ reference::kkeywordPrimary; $tag ]
Else If [ $menu = "n" ]
Set Field [ reference::knodePrimary; $tag ]
Else If [ $menu = "m" ]
Set Field [ reference::kmedium; $tag ]
Else If [ $menu = "h" ]
Set Field [ reference::kHealth; $tag ]
Else If [ $menu = "p" ]
Set Field [ reference::kfolderpath; $tag ]
Else If [ $menu = "o" ]
Set Field [ reference::korgan; $tag ]
Else If [ $menu = "c" and $$citationMatch ≠ "cite" ]
Set Field [ reference::kcopyist; $tag ]
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
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ reference::kkeywordPrimary; $find ]
Else If [ $menu = "n" ]
Set Field [ reference::knodePrimary; $find ]
Else If [ $menu = "m" ]
Set Field [ reference::kmedium; $find ]
Else If [ $menu = "h" ]
Set Field [ reference::kHealth; $find ]
Else If [ $menu = "p" ]
Set Field [ reference::kfolderpath; $find ]
Else If [ $menu = "o" ]
Set Field [ reference::korgan; $find ]
Else If [ $menu = "c" ]
Set Field [ reference::kcopyist; $find ]
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
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::filterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ reference::kkeywordPrimary; $find ]
Else If [ $menu = "n" ]
Set Field [ reference::knodePrimary; $find ]
Else If [ $menu = "m" ]
Set Field [ reference::kmedium; $find ]
Else If [ $menu = "h" ]
Set Field [ reference::kHealth; $find ]
Else If [ $menu = "p" ]
Set Field [ reference::kfolderpath; $find ]
Else If [ $menu = "o" ]
Set Field [ reference::korgan; $find ]
Else If [ $menu = "c" ]
Set Field [ reference::kcopyist; $find ]
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
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::filterFind; "main" & ¶ ]
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
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::filterFind; "main" & ¶ ]
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
Perform Script [ “loadCitation (update)” ]
#
#Return focus to Tag Menus window.
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
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use as a primary keyword."; Buttons: “OK” ]
Else If [ $$citationMatch = "node" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use as a primary node."; Buttons: “OK” ]
Else If [ $$citationMatch = "medium" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Buttons: “OK” ]
Else If [ $$citationMatch = "health" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Buttons: “OK” ]
Else If [ $$citationMatch = "path" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Buttons: “OK” ]
Else If [ $$citationMatch = "organ" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Buttons: “OK” ]
Else If [ $$citationMatch = "copyist" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Buttons: “OK” ]
Else If [ $$citationMatch = "cite" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use."; Buttons: “OK” ]
End If
#
#
End If
August 19, ଘ౮28 23:15:49 Library.fp7 - findPrimaryRef -1-
