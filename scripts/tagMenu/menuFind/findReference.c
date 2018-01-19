January 18, 2018 15:02:20 Library.fmp12 - findALL_LearnOrRefRecords -1-
reference: findALL_LearnOrRefRecords
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Exit find mode in the Tag Menus window, then click this button."; Default Button: “OK”,
Commit: “No” ]
Exit Script [ ]
End If
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
#
#As going to the other window will be involved
#stop the record load script on that window until
#this script is finished to speed things up and
#stop flashing effect.
Set Variable [ $$stoploadCitation; Value:1 ]
// Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
// Set Variable [ $$foundLayout ]
#
#Find all Learn records in a section. This would
#need to be done if the user was just in find mode
#on the tag screen and was showing only a few
#of a section's records using this mode.
If [ Get ( WindowName ) = "Learn" ]
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::note; ascending ]
[ Restore; No dialog ]
End If
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord (update name change loadCitation)” ]
Exit Script [ ]
End If
#
If [ Get ( WindowName ) = "References" ]
#find on reference layout ...
If [ Left (Get (LayoutName) ; 1) = "r" ]
Show All Records
#
#find on learn layout ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
End If
End If
#
#Omit locked records, which are the copyright
#images used by default copyright tags.
Constrain Found Set [ Specified Find Requests: Omit Records; Criteria: reference::lock: “lock” ]
[ Restore ]
#
#Sort and go to the first record. Due to bugs,
#two sorts are required to scroll the window to
#first record.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
If [ TEMP::InventoryLibraryYN = "" ]
#
#If reference is sorted by ...
If [ $$referenceSort = "" ]
#keyword
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "author" ]
#author
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByAuthor; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "dateCreated" ]
#dateCreated
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::createDate; descending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "dateModified" ]
#dateModified
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::modifyDate; descending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "datePublished" ]
#datePublished
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByDatePublished; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "publication" ]
#publication title
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByPublication; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "publisher" ]
#publisher's name
Sort Records [ Keep records in sorted order; Specified Sort Order: tagPublisher::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "title" ]
#title
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByTitle; ascending ]
[ Restore; No dialog ]
End If
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“testPulldownListANDsortOrderList”
tagKeywordPrimary::tag; ascending
reference::publicationYearOrStuffOrderNumber; based on value list: “testPulldownListANDsortOrderList”
reference::Title; ascending
reference::thoughtsNotesEtc; ascending ]
[ Restore; No dialog ]
End If
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord (update name change loadCitation)” ]
#
#
