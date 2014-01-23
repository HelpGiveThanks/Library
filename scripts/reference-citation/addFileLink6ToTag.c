reference(citation): addFileLink6ToTag
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
#Add ﬁle link to Tag Menu item.
Go to Field [ ]
If [ reference::Title ≠ "" and
FilterValues ( reference::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ and
reference::ﬁleName ≠ ""
 or
reference::Title ≠ "" and
FilterValues ( reference::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ and
reference::ﬁleName ≠ ""
 or
reference::Title ≠ "" and
FilterValues ( reference::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ and
tagRefFolderPath::tag ≠ "" and
reference::ﬁleName ≠ ""
 or
FilterValues ( testlearn::kﬁleLocation ; "8162011225532313" ) = "8162011225532313" & ¶ and
testlearn::ﬁlename ≠ ""
 or
FilterValues ( testlearn::kﬁleLocation ; "8162011225558314" ) = "8162011225558314" & ¶ and
testlearn::ﬁlename ≠ ""
 or
FilterValues ( testlearn::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ and
tagTLFolderPath::tag ≠ "" and
testlearn::ﬁlename ≠ ""
 or
testlearn::URL ≠ ""
 or
reference::URL ≠ "" ]
Set Variable [ $$name; Value:"title" ]
Set Variable [ $$number; Value:3 ]
#
#If the ﬁlterFind checkbox is not checked for the
#the current $$CitationMatch variable, then
#these next scripts will identify that problem,
#ﬁx it, and inform the user of what it did.
If [ Get ( LayoutTableName ) = "testlearn" ]
If [ $$citationMatch = "key" and "keyword" & ¶ ≠ FilterValues ( testlearn::ﬁlterFind ; "keyword" ) ]
Set Variable [ $ﬁlterFind; Value:testlearn::ﬁlterFind ]
Set Field [ testlearn::ﬁlterFind; "keyword" & ¶ & $ﬁlterFind ]
// Show Custom Dialog [ Message: "The system has added this learn record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to ﬁnd it for " & If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, ﬁle and web links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Buttons: “OK” ]
Else If [ $$citationMatch & ¶ ≠ FilterValues ( testlearn::ﬁlterFind ; $$citationMatch ) ]
Set Variable [ $ﬁlterFind; Value:testlearn::ﬁlterFind ]
Set Field [ testlearn::ﬁlterFind; $$citationMatch & ¶ & $ﬁlterFind ]
// Show Custom Dialog [ Message: "The system has added this learn record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to ﬁnd it for " & If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, ﬁle and web links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Buttons: “OK” ]
End If
#
Else If [ Get ( LayoutTableName ) = "reference" ]
If [ $$citationMatch = "key" and "keyword" & ¶ ≠ FilterValues ( reference::ﬁlterFind ; "keyword" ) ]
Set Variable [ $ﬁlterFind; Value:reference::ﬁlterFind ]
Set Field [ reference::ﬁlterFind; "keyword" & ¶ & $ﬁlterFind ]
// Show Custom Dialog [ Message: "The system has added this reference record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to ﬁnd it for " & If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, ﬁle and web links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Buttons: “OK” ]
Else If [ $$citationMatch & ¶ ≠ FilterValues ( reference::ﬁlterFind ; $$citationMatch ) ]
Set Variable [ $ﬁlterFind; Value:reference::ﬁlterFind ]
Set Field [ reference::ﬁlterFind; $$citationMatch & ¶ & $ﬁlterFind ]
// Show Custom Dialog [ Message: "The system has added this reference record to the " &
If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) &
 " citation record set. You will not have to click the 'all' button anymore to ﬁnd it for " & If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."
//Next time you click on the add button, this record will be found as part of the records supplying pictures, ﬁle and web links to " &
//If ( $$citationMatch = "key" ; "keyword (key)" ; $$citationMatch ) & " tags."; Buttons: “OK” ]
End If
End If
#
#Now perform the script that adds the tag.
Perform Script [ “CHUNKaddLinkToTag” ]
Exit Script [ ]
End If
#
If [ reference::ﬁleName = "" and Get ( LayoutTableName ) = "reference" or testlearn::ﬁlename = "" and Get ( LayoutTableName ) = "testlearn" ]
Show Custom Dialog [ Message: "A ﬁle name is required including the ﬁle's extension: .jpg , .gif , .pdf , .mov , etc. OR a URL is required to add a link."; Buttons: “OK” ]
Else If [ reference::kﬁleLocation = "" and reference::ﬁleName ≠ "" and Get ( LayoutTableName ) = "reference" or testlearn::kﬁleLocation = "" and testlearn::ﬁlename ≠ "" and Get ( LayoutTableName ) = "testlearn" ]
Show Custom Dialog [ Message: "Check the box next the location of your ﬁle: main, other, or x."; Buttons: “OK” ]
Else If [ FilterValues ( reference::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ and
tagRefFolderPath::tag = "" or
FilterValues ( testlearn::kﬁleLocation ; "8162011225605315" ) = "8162011225605315" & ¶ and
testlearn::kfolderPath = "" ]
Show Custom Dialog [ Message: "Select a ﬁle path from the Tag Menus window. If there are none then add one by opening the ﬁle with a browser (Firefox, Explore, etc.) and dragging/pasting the address into a new tag's text box."; Buttons: “OK” ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Perform Script [ “menuPath” ]
End If
January 7, 平成26 17:58:03 Imagination Quality Management.fp7 - addFileLink6ToTag -1-
