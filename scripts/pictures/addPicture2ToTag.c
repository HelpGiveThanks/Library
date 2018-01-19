January 15, 2018 17:58:24 Library.fmp12 - addPicture2ToTag -1-
pictures: addPicture2ToTag
#
#If user was in the copyright window then
#return user to this window.
If [ $$userInCopyrightWindow = 1 ]
Show Custom Dialog [ Message: "For copyright records, there is only one picture allowed."; Default Button: “OK”, Commit:
“Yes” ]
Exit Script [ ]
End If
#
#Note which button has been clicked ( 1, 2 or 3)
#and if there is a picture to show then link it
#to tag user is currently wanting to link it to.
If [ reference::picture ≠ ""
or
reference::showMedia ≠ "" and reference::URL ≠ ""
or
reference::showMedia[2] ≠ "" and reference::fileName ≠ "" ]
Set Variable [ $$name; Value:"picture" ]
Set Variable [ $$number; Value:2 ]
#
#If the filterFind checkbox is not checked for the
#the current $$CitationMatch variable, then
#these next scripts will identify that problem,
#fix it, and inform the user of what it did.
If [ $$citationMatch = "key" ]
If [ "keyword" ≠ GetValue ( FilterValues ( reference::filterFind ; "keyword" ) ; 1 ) ]
Set Variable [ $filterFind; Value:reference::filterFind ]
Set Field [ reference::filterFind; "keyword" & ¶ & $filterFind ]
// Show Custom Dialog [ Message: "The system has added this reference record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to find it for " & If ( $$citationMatch = "key" ;
"keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, file and
web links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Default Button: “OK”, Commit: “No” ]
End If
Else If [ $$citationMatch & ¶ ≠ FilterValues ( reference::filterFind ; $$citationMatch & ¶) ]
Set Variable [ $filterFind; Value:reference::filterFind ]
Set Field [ reference::filterFind; $$citationMatch & ¶ & $filterFind ]
// Show Custom Dialog [ Message: "The system has added this reference record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to find it for " & If ( $$citationMatch = "key" ;
"keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, file and web
links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Default Button: “OK”, Commit: “No” ]
End If
#
#Now perform the script that adds the tag.
Perform Script [ “CHUNKaddPictureToTag (update)” ]
End If
#
