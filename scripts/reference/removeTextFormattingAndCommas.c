January 18, 2018 15:40:34 Library.fmp12 - removeTextFormattingAndCommas -1-
reference: removeTextFormattingAndCommas
#
#
#Stop script if running it slows down another
#script looping thru multiple records.
If [ $$stopTest ≠ "" ]
Exit Script [ ]
End If
#
#
#Insure changes made to current record are
#noticed by the script steps below.
Commit Records/Requests
#
#Remove formatting.
Set Field [ tagMenus::tag; TextFontRemove ( tagMenus::tag ) ]
Set Field [ tagMenus::tag; TextFormatRemove ( tagMenus::tag ) ]
Set Field [ tagMenus::tag; TextSizeRemove ( tagMenus::tag ) ]
#
#Remove any white spaces in front or after tag.
Set Field [ tagMenus::tag; Trim ( tagMenus::tag ) ]
#
#Capture tag.
Set Variable [ $tag; Value:tagMenus::tag ]
#
#Remove punctuation on key and node tag tags
#that will stop the library from keeping track of them.
If [ Filter ( tagMenus::tag ; "," ) = "," and $$citationMatch = "key" ]
Show Custom Dialog [ Message: "commas prevent system from keeping track of this item and have been removed"; Default
Button: “OK”, Commit: “Yes” ]
Set Field [ tagMenus::tag; Substitute ( $tag ; "," ; "" ) ]
Else If [ Filter ( tagMenus::tag ; ";" ) = ";" and $$citationMatch = "node" ]
Show Custom Dialog [ Message: "semicolons prevent system from keeping track of this item and have been removed"; Default
Button: “OK”, Commit: “Yes” ]
Set Field [ tagMenus::tag; Substitute ( $tag ; ";" ; "" ) ]
End If
#
#On brainstorm, copyright, path, publication
#and publisher layouts run spell check script.
#This is neccessary because the exit script
#trigger, which on key and node layouts runs
#this script, used by this formatting script,
#and so it need to trigger the spellcheck.
If [ $$citationmatch = "brainstorm"
 or
$$citationmatch = "copyright"
 or
$$citationmatch = "path"
 or
$$citationmatch = "publication"
 or
$$citationmatch = "publisher" ]
Perform Script [ “CHUNKcheckForDragPasteChanges” ]
End If
#
#If on the Tag Menus path layout ...
If [ $$citationMatch = "path" and tagMenus::tag ≠ "" ]
#
If [ $$stopFilePathWarning ≠ 1 ]
#
#If the real checkbox is checked tell user this.
If [ tagMenus::kfileORkTestItemCreatorNode ≠ "" ]
Show Custom Dialog [ Message: "File path to a folder on a computer? " & ¶ & " Uncheck the 'real shelf, box, etc.'
checkbox."; Default Button: “OK”, Commit: “Yes” ]
#
#
#If the real checkbox is NOT checked tell user
#this and check the folder path that they enter.
Else
#
#Make sure path does NOT begin
#with a forward slash.
If [ Left ( tagMenus::tag ; 1 ) = "/" ]
Set Field [ tagMenus::tag; Middle ( $tag ; 2 ; 1000 ) ]
Set Field [ tagMenus::tagSpelling; Middle ( $tag ; 2 ; 1000 ) ]
#
#Capture updated tag.
Set Variable [ $tag; Value:tagMenus::tag ]
Show Custom Dialog [ Message: "Filepaths cannot begin forward slash / or they will not work. The beginning
forward slash has been removed for you."; Default Button: “OK”, Commit: “Yes” ]
End If
#
#Make sure path ends with a forward slash.
If [ Right ( tagMenus::tag ; 1 ) ≠ "/" ]
Set Field [ tagMenus::tag; $tag & "/" ]
Set Field [ tagMenus::tagSpelling; $tag & "/" ]
Show Custom Dialog [ Message: "All filepaths must end with forward slash / or they will not work. One has been
added for you."; Default Button: “OK”, Commit: “No” ]
End If
#
Show Custom Dialog [ Message: "Make sure this file Path does not end with a file Name." & ¶ & " Real location? "
& ¶ & " Check the 'real shelf, box, etc.' checkbox."; Default Button: “OK”, Commit: “Yes” ]
#
#Now test open folder for user.
Show Custom Dialog [ Message: "The library will now test this filepath to insure it opens this folder."; Default Button:
“OK”, Commit: “Yes” ]
#
#Use %20 space substitutes.
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagMenus::tag ; " " ; "%20" ) ]
[ No dialog ]
If [ Get ( LastError ) ≠ 0 ]
#If that failes, try spaces.
Open URL [ Substitute ( Case ( Get ( SystemPlatform ) = - 2 ; "file:/" ; "file:///" ) & tagMenus::tag ; " " ; " " ) ]
[ No dialog ]
End If
If [ Get (LastError) = 5 ]
Show Custom Dialog [ Message: "This file path is not working. A valid path should look something like this >>>
/users/you/documents/other folder/"; Default Button: “OK”, Commit: “Yes” ]
End If
End If
End If
End If
