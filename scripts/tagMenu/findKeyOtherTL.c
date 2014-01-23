tagMenu: FindKeyOtherTL
#Select tag to be found.
Set Variable [ $tag; Value:tagMenus::_Ltag ]
#
#
#Select the kind of tag to be found. We grab
#only the ﬁrst three letters because the shortest
#menu item 'key' has only three letters, and because
#we need the same number of characters/letters
#to make up this variable so when it is added to
#the ﬁrst part of an item in the found list below
#it can be removed by the system which only
#can be told how many characters to remove.
#This variable is thus a meta tag added to an
#ID number to tell the system from which menu
#did this item come. This meta tag or tag allows
#us to make a list of ID numbers from various
#tag menus: key, node, medium, etc.
Set Variable [ $menu; Value:Left ( $$citationMatch ; 1 ) ]
#
#Get the name of the tag for error message
#at bottom of this script if needed.
Set Variable [ $name; Value:tagMenus::tag ]
#
#As going to the other window will be involved
#stop the record load script on that window until
#this script is ﬁnished to speed things up and
#stop ﬂashing effect.
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Go to the other window and start the ﬁnd process.
Select Window [ Name: "Learn"; Current ﬁle ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
// Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
#
#
If [ $$citationMatch = "key" ]
Set Field [ testlearn::kcKeywordOther; $tag ]
Else If [ $$citationMatch = "node" ]
Set Field [ testlearn::kNodeOther; $tag ]
End If
#
#
#If this is the ﬁrst ﬁnd, note this and perform
#the ﬁnd.
If [ $$ﬁrstFindOther = "" ]
Set Variable [ $$ﬁrstFindOther; Value:1 ]
Set Variable [ $$foundOther; Value:$menu & $tag & ¶ ]
Perform Find [ ]
#
#If nothing was found capture the error message
#as steps before showing the error message will
#delete it from the system and we need it to
#activate the error message below if there was
#an error.
Set Variable [ $error; Value:Get (LastError) ]
#
#If this is not the ﬁrst ﬁnd and the item that
#the user clicked on to start this script has
#not already been found, then add items tagged
#with it to the current set of found records.
Else If [ $$ﬁrstFindOther = 1 ]
If [ $menu & $tag & ¶ ≠ FilterValues ( $$foundOther ; $menu & $tag) ]
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
Set Variable [ $found; Value:$$foundOther ]
Set Variable [ $$foundOther; Value:$menu & $tag & ¶ & $found ]
#
#If this is not the ﬁrst ﬁnd and the item that
#the user clicked on to start this script has
#already been found, then remove tag from the
#the list of found other tagged records.
Else If [ $menu & $tag & ¶= FilterValues ( $$foundOther ; $menu & $tag & ¶) ]
Set Variable [ $found; Value:$$foundOther ]
Set Variable [ $$foundOther; Value:Substitute ( $found ; $menu & $tag & ¶ ; "" ) ]
#
#Enter browse mode to clear the ﬁnd selections
#set at the beginning of this script.
Enter Browse Mode
#
#If after removing this item from the list of found other
#tagged records the list is empty, perform a ﬁnd
#that will result in zero records being found
#to reﬂect the fact that the user currently has
#an empty found other list.
If [ $$foundOther = "" ]
Set Variable [ $$ﬁrstFindOther ]
Enter Find Mode [ ]
#
#
#Since ID numbers are numbers, the text
#'ﬁndnoRecords' entered in the ID ﬁeld will result
#in zero records being found.
If [ $$citationMatch = "key" ]
Set Field [ testlearn::kcKeywordOther; "ﬁndNoRecords" & ¶ ]
Else If [ $$citationMatch = "node" ]
Set Field [ testlearn::kNodeOther; "ﬁndNoRecords" & ¶ ]
End If
#
#
Perform Find [ ]
#
#If after removing this item from the $$foundOther
#list, the list is not empty, reﬁnd all records
#still on the list one tag at a time.
Else If [ $$foundOther ≠ "" ]
#
January 7, 平成26 16:40:37 Imagination Quality Management.fp7 - FindKeyOtherTL -1-tagMenu: FindKeyOtherTL
#Create a copy of the found list. Items will be
#removed from this one at a time as they are found.
Set Variable [ $ﬁndList; Value:$$foundOther ]
#
#Get the menu item name so system will know
#what ﬁeld to put the ID number into to ﬁnd
#records tagged with this item.
Set Variable [ $menu; Value:Left ( ( GetValue ( $ﬁndList ; 1 ) ) ; 1 ) ]
#
#Get the ID number of the tag to be found.
#(the number 42 is a joke, essentially the number
#needs to be big enough to capture the full ID number
#which is much shorter, but overkill doesn't hurt)
#FYI: joke is from Hitchhiker's Guide to the Galaxy
Set Variable [ $ﬁnd; Value:Middle ( ( GetValue ( $ﬁndList ; 1 ) ) ; 2 ; 42 ) ]
#
#Remove it from the list of tags to be found.
Set Variable [ $subtract; Value:$ﬁndList ]
Set Variable [ $ﬁndList; Value:Substitute ( $subtract ; $menu & $ﬁnd & ¶ ; "" ) ]
#
#Find main window records tagged with it.
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ testlearn::kcKeywordOther; $ﬁnd ]
Else If [ $menu = "n" ]
Set Field [ testlearn::kNodeOther; $ﬁnd ]
End If
#
#
#If there is more than one item on the $$found
#list, then ﬁnd the rest of records tagged with
#this items/tags.
Perform Find [ ]
Loop
#
#When the list is empty stop ﬁnding stuff.
Exit Loop If [ ValueCount ( $ﬁndList ) = 0 ]
#
#Get the menu item name so system will know
#what ﬁeld to put the ID number into to ﬁnd
#records tagged with this item.
Set Variable [ $menu; Value:Left ( ( GetValue ( $ﬁndList ; 1 ) ) ; 1 ) ]
#
#Get the ID number of the tag to be found.
Set Variable [ $ﬁnd; Value:Middle ( ( GetValue ( $ﬁndList ; 1 ) ) ; 2; 42 ) ]
#
#Remove it from the list of tags to be found.
Set Variable [ $subtract; Value:$ﬁndList ]
Set Variable [ $ﬁndList; Value:Substitute ( $subtract ; $menu & $ﬁnd & ¶ ; "" ) ]
#
#Find main window records tagged with it.
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ testlearn::kcKeywordOther; $ﬁnd ]
Else If [ $menu = "n" ]
Set Field [ testlearn::kNodeOther; $ﬁnd ]
End If
#
#
Extend Found Set [ ]
End Loop
End If
End If
End If
#
#Reﬁnd primary items.
If [ $$found ≠ "" ]
#
#Create a copy of the found list. Items will be
#removed from this one at a time as they are found.
Set Variable [ $ﬁndList; Value:$$found ]
#
#Get the menu item name so system will know
#what ﬁeld to put the ID number into to ﬁnd
#records tagged with this item.
Set Variable [ $menu; Value:Left ( ( GetValue ( $ﬁndList ; 1 ) ) ; 1 ) ]
#
#Get the ID number of the tag to be found.
#(the number 42 is a joke, essentially the number
#needs to be big enough to capture the full ID number
#which is much shorter, but overkill doesn't hurt)
#FYI: joke is from Hitchhiker's Guide to the Galaxy
Set Variable [ $ﬁnd; Value:Middle ( ( GetValue ( $ﬁndList ; 1 ) ) ; 2 ; 42 ) ]
#
#Remove it from the list of tags to be found.
Set Variable [ $subtract; Value:$ﬁndList ]
Set Variable [ $ﬁndList; Value:Substitute ( $subtract ; $menu & $ﬁnd & ¶ ; "" ) ]
#
#Find main window records tagged with it.
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ testlearn::kKeywordPrimary; $ﬁnd ]
Else If [ $menu = "n" ]
Set Field [ testlearn::kNodePrimary; $ﬁnd ]
Else If [ $menu = "m" ]
Set Field [ testlearn::kmedium; $ﬁnd ]
Else If [ $menu = "h" ]
Set Field [ testlearn::kHealth; $ﬁnd ]
Else If [ $menu = "r" ]
Set Field [ testlearn::kcreference; $ﬁnd ]
Else If [ $menu = "c" ]
Set Field [ testlearn::kcitation; $ﬁnd ]
Else If [ $menu = "p" ]
Set Field [ testlearn::kfolderPath; $ﬁnd ]
Else If [ $menu = "t" ]
January 7, 平成26 16:40:37 Imagination Quality Management.fp7 - FindKeyOtherTL -2-tagMenu: FindKeyOtherTL
Set Field [ testlearn::ktest; $ﬁnd ]
Else If [ $menu = "s" ]
Set Field [ testlearn::kcsample; $ﬁnd ]
End If
#
#
Extend Found Set [ ]
#
#If there is more than one item on the $$found
#list, then ﬁnd the rest of records tagged with
#this items/tags.
Loop
#
#When the list is empty stop ﬁnding stuff.
Exit Loop If [ ValueCount ( $ﬁndList ) = 0 ]
#
#Get the menu item name so system will know
#what ﬁeld to put the ID number into to ﬁnd
#records tagged with this item.
Set Variable [ $menu; Value:Left ( ( GetValue ( $ﬁndList ; 1 ) ) ; 1 ) ]
#
#Get the ID number of the tag to be found.
Set Variable [ $ﬁnd; Value:Middle ( ( GetValue ( $ﬁndList ; 1 ) ) ; 2 ; 42 ) ]
#
#Remove it from the list of tags to be found.
Set Variable [ $subtract; Value:$ﬁndList ]
Set Variable [ $ﬁndList; Value:Substitute ( $subtract ; $menu & $ﬁnd & ¶ ; "" ) ]
#
#Find main window records tagged with it.
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
#
#
If [ $menu = "k" ]
Set Field [ testlearn::kKeywordPrimary; $ﬁnd ]
Else If [ $menu = "n" ]
Set Field [ testlearn::kNodePrimary; $ﬁnd ]
Else If [ $menu = "m" ]
Set Field [ testlearn::kmedium; $ﬁnd ]
Else If [ $menu = "h" ]
Set Field [ testlearn::kHealth; $ﬁnd ]
Else If [ $menu = "r" ]
Set Field [ testlearn::kcreference; $ﬁnd ]
Else If [ $menu = "c" ]
Set Field [ testlearn::kcitation; $ﬁnd ]
Else If [ $menu = "p" ]
Set Field [ testlearn::kfolderPath; $ﬁnd ]
Else If [ $menu = "t" ]
Set Field [ testlearn::ktest; $ﬁnd ]
Else If [ $menu = "s" ]
Set Field [ testlearn::kcsample; $ﬁnd ]
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
#Go to ﬁrst record and preform record load script.
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
#
#Return focus to Tag Menus window.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
#If no records where found tell user why and
#remove tag ID from list of tags attached to records
#in the main window.
If [ $error = 401 ]
If [ $$ﬁrstFind = "" ]
Set Variable [ $$foundOther ]
Else If [ $$ﬁrstFind ≠ "" ]
Set Variable [ $$foundOther; Value:Substitute ( $found ; $menu & $tag & ¶ ; "" ) ]
End If
Refresh Window
#
#
If [ $$citationMatch = "key" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use as an other keyword."; Buttons: “OK” ]
Else If [ $$citationMatch = "node" ]
Show Custom Dialog [ Message: "'" & $name & "'" & " is not in use as a primary node."; Buttons: “OK” ]
End If
#
#
End If
January 7, 平成26 16:40:37 Imagination Quality Management.fp7 - FindKeyOtherTL -3-
