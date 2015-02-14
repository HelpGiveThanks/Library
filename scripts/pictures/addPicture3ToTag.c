pictures: addPicture3ToTag
#
#Do not allow learn records to be added to tags as
#that would require insuring all that Learn record's
#reference records tagged onto it were also
#brought into the new section along with all
#their tags, and their tags' tags. THUS only allow
#Learn records to be added to tags that have a picture
#or link (thus provide value) and have none of the
#above mentioned tags: reference, cite.
#AND once such a tag is added no reference,
#or cite tags can be added to it.
If [ testlearn::kcitation ≠ "" or testlearn::kcreference ≠ "" ]
Show Custom Dialog [ Message: "Learn records with references or a citation cannot be added to tags. Doing so would require adding all these reference and cite records' references and cite records, and then all of theirs, and so on. "; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Note which button has been clicked ( 1, 2 or 3)
#and if there is a picture to show then link it
#to tag user is currently wanting to link it to.
If [ reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "jpg"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "gif"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "eps"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "jp2"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "psd"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "png"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "pct"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "pcs"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = ".qt"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "sgi"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tga"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "tif"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "bmp"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "wmf"
or reference::kfileLocation ≠ "" and reference::fileName ≠ "" and Right ( reference::fileName ; 3 ) = "emf"
or Right ( reference::URL ; 3 ) = "jpg"
or Right ( reference::URL ; 3 ) = "gif"
or Right ( reference::URL ; 3 ) = "eps"
or Right ( reference::URL ; 3 ) = "jp2"
or Right ( reference::URL ; 3 ) = "psd"
or Right ( reference::URL ; 3 ) = "png"
or Right ( reference::URL ; 3 ) = "pct"
or Right ( reference::URL ; 3 ) = "pcs"
or Right ( reference::URL ; 3 ) = ".qt"
or Right ( reference::URL ; 3 ) = "sgi"
or Right ( reference::URL ; 3 ) = "tga"
or Right ( reference::URL ; 3 ) = "tif"
or Right ( reference::URL ; 3 ) = "bmp"
or Right ( reference::URL ; 3 ) = "wmf"
or Right ( reference::URL ; 3 ) = "emf"
or
reference::picture ≠ "" ]
Set Variable [ $$name; Value:"picture" ]
Set Variable [ $$number; Value:3 ]
#
#If the filterFind checkbox is not checked for the
#the current $$CitationMatch variable, then
#these next scripts will identify that problem,
#fix it, and inform the user of what it did.
If [ Get ( LayoutTableName ) = "testlearn" ]
If [ $$citationMatch = "key" ]
If [ "keyword" & ¶ ≠ FilterValues ( testlearn::filterFind ; "keyword" & ¶ ) ]
Set Variable [ $filterFind; Value:testlearn::filterFind ]
Set Field [ testlearn::filterFind; "keyword" & ¶ & $filterFind ]
// Show Custom Dialog [ Message: "The system has added this learn record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to find it for " & If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, file and web links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Buttons: “OK” ]
End If
Else If [ $$citationMatch & ¶ ≠ FilterValues ( testlearn::filterFind ; $$citationMatch & ¶ ) ]
Set Variable [ $filterFind; Value:testlearn::filterFind ]
Set Field [ testlearn::filterFind; $$citationMatch & ¶ & $filterFind ]
// Show Custom Dialog [ Message: "The system has added this learn record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to find it for " & If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, file and web links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Buttons: “OK” ]
End If
#
Else If [ Get ( LayoutTableName ) = "reference" ]
If [ $$citationMatch = "key" ]
If [ "keyword" & ¶ ≠ FilterValues ( reference::filterFind ; "keyword" & ¶) ]
Set Variable [ $filterFind; Value:reference::filterFind ]
Set Field [ reference::filterFind; "keyword" & ¶ & $filterFind ]
// Show Custom Dialog [ Message: "The system has added this reference record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to find it for " & If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, file and web links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Buttons: “OK” ]
End If
Else If [ $$citationMatch & ¶ ≠ FilterValues ( reference::filterFind ; $$citationMatch & ¶) ]
Set Variable [ $filterFind; Value:reference::filterFind ]
Set Field [ reference::filterFind; $$citationMatch & ¶ & $filterFind ]
// Show Custom Dialog [ Message: "The system has added this reference record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to find it for " & If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, file and web links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Buttons: “OK” ]
End If
End If
#
#Now perform the script that adds the tag.
Perform Script [ “CHUNKaddPictureToTag” ]
End If
January 7, 平成26 17:16:32 Imagination Quality Management.fp7 - addPicture3ToTag -1-
