tagMenu: menuFind: findReference
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Exit find mode in the Tag Menus window, then click this button."; Buttons: “OK” ]
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
If [ $$referenceSort = 2 ]
Sort Records [ Specified Sort Order: reference::modifyDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "" ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = 1 ]
Sort Records [ Specified Sort Order: reference::createDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
End If
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
If [ $$add = 1 ]
Show Custom Dialog [ Message: "Find learn, or
test discovery, or
both types of records?"; Buttons: “learn”, “discovery”, “both” ]
Enter Find Mode [ ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Field [ testlearn::kcsection; "*" ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ testlearn::kaudienceLocation; "*" ]
Else If [ Get ( LastMessageChoice ) = 3 ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
End If
Show Custom Dialog [ Message: "limit find to just this section -- " & TEMP::sectionName & " -- or find for entire library?";
Buttons: “section”, “library” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Field [ reference::kcsection; "==" & TEMP::ksection ]
Else If [ Get ( LastMessageChoice ) = 2 ]
End If
Else If [ $$add ≠ 1 ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
End If
Perform Find [ ]
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
Exit Script [ ]
End If
#
If [ Get ( WindowName ) = "References" ]
#find on reference layout ...
If [ Left (Get (LayoutName) ; 1) = "r" and $$add ≠ "" ]
Show Custom Dialog [ Message: "Find all reference records for the " & TEMP::sectionName & " section or show references
for all sections in the library?"; Buttons: “section”, “all” ]
Enter Find Mode [ ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Field [ reference::kcsection; TEMP::ksection ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::kcsection; "*" ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "r" and $$add = "" ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
#
#find on learn layout ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
End If
Else If [ Get ( WindowName ) = "Tag Menus" ]
Show Custom Dialog [ Message: "Find all reference records for the " & TEMP::sectionName & " section or show references for
all sections in the library?"; Buttons: “section”, “all” ]
Enter Find Mode [ ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Field [ reference::kcsection; "==" & TEMP::ksection ]
Else If [ Get ( LastMessageChoice ) = 2 ]
Set Field [ reference::kcsection; "*" ]
End If
End If
Perform Find [ ]
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
Select Window [ Name: "Tag Menus"; Current file ]
January 8, ଘ౮28 14:39:45 Library.fp7 - findReference -1-
