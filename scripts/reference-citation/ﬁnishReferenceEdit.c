reference(citation): finishReferenceEdit
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
Select Window [ Name: "References"; Current file ]
#
#If the media and media type have not been selected then tell user these fields are required before exiting the reference record.
If [ reference::kmedia = "" and TEMP::InventoryLibaryYN = ""
or
reference::kmediaType = "" and TEMP::InventoryLibaryYN = "" ]
Show Custom Dialog [ Message: "REQUIRED: media (book, journal article, etc.) and media type (web, CD, paper, etc.) identification."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Continue with going back to reference layout.
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
#Go to reference record layout.
If [ TEMP::InventoryLibaryYN ≠ "" ]
Go to Layout [ “ReferenceStuff” (reference) ]
Else
Go to Layout [ “Reference” (reference) ]
End If
#
#Allow add mode.
Set Variable [ $$stopAdd ]
#
#Close reference help window if open.
Close Window [ Name: "Reference Field Help"; Current file ]
Set Variable [ $$turnOffThisScript ]
May 10, 平成27 12:21:34 Library.fp7 - finishReferenceEdit -1-
