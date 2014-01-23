reference(citation): ﬁnishReferenceEdit
#
#If user is in tag ﬁeld and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Field [ ]
Select Window [ Name: "References"; Current ﬁle ]
#
#If the media and media type have not been selected then tell user these ﬁelds are required before exiting the reference record.
If [ reference::kmedia = "" or reference::kmediaType = "" ]
Show Custom Dialog [ Message: "REQUIRED: media (book, journal article, etc.) and media type (web, CD, paper, etc.) identiﬁcation."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Continue with going back to reference layout.
If [ $$referenceSort = 2 ]
Sort Records [ Speciﬁed Sort Order: reference::modifyDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "" ]
Sort Records [ Speciﬁed Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = 1 ]
Sort Records [ Speciﬁed Sort Order: reference::createDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
End If
#
#Go to reference record layout.
Go to Layout [ “Reference” (reference) ]
#
#Allow add mode.
Set Variable [ $$stopAdd ]
#
#Close reference help window if open.
Close Window [ Name: "Reference Field Help"; Current ﬁle ]
Set Variable [ $$turnOffThisScript ]
January 7, 平成26 17:49:40 Imagination Quality Management.fp7 - ﬁnishReferenceEdit -1-
