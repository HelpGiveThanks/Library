reference(citation): duplicateReferenceRecord
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If in ﬁnd mode, exit script.
If [ $$ﬁndMode ≠ "" ]
Show Custom Dialog [ Message: "Cancel ﬁnd mode, then click this button."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If in ﬁnd mode, exit ﬁnd mode.
If [ $$ﬁndMode= 1 ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Set Variable [ $$ﬁndMode ]
Set Variable [ $$ﬁrstFind ]
Set Variable [ $$ﬁrstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Go to Layout [ $$ﬁndLayout ]
Set Variable [ $$stoploadCitation ]
Select Window [ Name: "References"; Current ﬁle ]
End If
#
#If user is in tag ﬁeld and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Field [ ]
Select Window [ Name: "References"; Current ﬁle ]
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
Set Variable [ $$stoploadCitation; Value:1 ]
#
Set Variable [ $type; Value:reference::kmediaType ]
Set Variable [ $media; Value:reference::kmedia ]
Set Variable [ $typeOther; Value:reference::TypeOfMediumOther ]
#
Set Variable [ $P; Value:reference::kkeywordPrimary ]
Set Variable [ $O; Value:reference::kkeywordOther ]
Set Variable [ $Owords; Value:reference::OtherKeyWords ]
#$$nodeprimary is already known by the system.
Set Variable [ $NodeOthers; Value:reference::NodeOthers ]
Set Variable [ $authorList; Value:reference::referenceNodes ]
Set Variable [ $authorListOLD; Value:reference::referenceNodesOLD ]
Set Variable [ $title; Value:reference::Title ]
#
Set Variable [ $picture; Value:reference::picture ]
#
Set Variable [ $chapter; Value:reference::bookChapter ]
Set Variable [ $dissertation; Value:reference::dissertationThesisUniversity ]
Set Variable [ $govt; Value:reference::governmentAuthor ]
Set Variable [ $govtDoc; Value:reference::GovernmentDocInfo ]
Set Variable [ $letter; Value:reference::letterDate ]
Set Variable [ $email; Value:reference::emailRecipient ]
Set Variable [ $ctitle; Value:reference::compilationTitle ]
Set Variable [ $ceditor; Value:reference::compilationEditors ]
Set Variable [ $cnumber; Value:reference::compilationNumberOfEditors ]
Set Variable [ $cAbbr; Value:reference::compilationAbbr ]
Set Variable [ $conIntro; Value:reference::conferenceIntroWords ]
Set Variable [ $conTitle; Value:reference::conferenceTitle ]
Set Variable [ $conSubTitle; Value:reference::conferenceSubTitle ]
Set Variable [ $conGname; Value:reference::conferenceGroupName ]
Set Variable [ $conLocation; Value:reference::conferenceLocation ]
Set Variable [ $conDate; Value:reference::conferenceDate ]
#
Set Variable [ $volumeNumber; Value:reference::volumeNumber ]
Set Variable [ $issueNumber; Value:reference::issueNumber ]
Set Variable [ $pageNumberRange; Value:reference::pageNumberRange ]
#
Set Variable [ $noPP; Value:reference::pageNumberOther ]
#
Set Variable [ $TimeRange; Value:reference::TimeRange ]
Set Variable [ $copyrightHolder; Value:reference::kcopyrightHolder ]
#
Set Variable [ $notPub; Value:reference::publisherTypeAlternative ]
Set Variable [ $notPubOther; Value:reference::publisherTypeOther ]
Set Variable [ $pubLocation; Value:reference::publisherLocation ]
#
Set Variable [ $pubYear; Value:reference::pubYear ]
#
Set Variable [ $pubDate; Value:reference::PubDate ]
Set Variable [ $pubDateOther; Value:reference::pubDateOther ]
#
Set Variable [ $copyrightYear; Value:reference::CopyrightYear ]
#
Set Variable [ $copyrightOtherHolder; Value:reference::copyrightOtherHolder ]
#
Set Variable [ $URL; Value:reference::URL ]
Set Variable [ $URLdate; Value:reference::URLdate ]
#
Set Variable [ $library; Value:reference::library only ]
Set Variable [ $isbn; Value:reference::ISBN ]
Set Variable [ $doi; Value:reference::URLdoi ]
Set Variable [ $issn; Value:reference::ISSN ]
#
Set Variable [ $ﬁleName; Value:reference::ﬁleName ]
Set Variable [ $InFolder; Value:reference::kﬁleLocation ]
Set Variable [ $citation; Value:reference::kcitation ]
Set Variable [ $notes; Value:reference::thoughtsNotesEtc ]
Set Variable [ $refDump; Value:reference::referenceDump ]
#
Set Variable [ $rights; Value:reference::rights ]
Go to Field [ ]
New Record/Request
January 7, 平成26 17:40:56 Imagination Quality Management.fp7 - duplicateReferenceRecord -1-reference(citation): duplicateReferenceRecord
#
#
Set Field [ reference::kmediaType; $type ]
Set Field [ reference::kmedia; $media ]
Set Field [ reference::TypeOfMediumOther; $typeOther ]
#
Set Field [ reference::kkeywordPrimary; $P ]
Set Field [ reference::kkeywordOther; $O ]
Set Field [ reference::OtherKeyWords; $Owords ]
Set Field [ reference::knodePrimary; $$primaryNode ]
Set Field [ reference::knodeOther; $$node ]
Set Field [ reference::NodeOthers; $NodeOthers ]
Set Field [ reference::referenceNodes; $authorList ]
Set Field [ reference::referenceNodesOLD; $authorListOLD ]
Set Field [ reference::Title; $title ]
#
Set Field [ reference::picture; $picture ]
#
Set Field [ reference::bookChapter; $chapter ]
Set Field [ reference::dissertationThesisUniversity; $dissertation ]
Set Field [ reference::governmentAuthor; $govt ]
Set Field [ reference::GovernmentDocInfo; $govtDoc ]
Set Field [ reference::letterDate; $letter ]
Set Field [ reference::emailRecipient; $email ]
Set Field [ reference::compilationTitle; $ctitle ]
Set Field [ reference::compilationEditors; $ceditor ]
Set Field [ reference::compilationNumberOfEditors; $cnumber ]
Set Field [ reference::compilationAbbr; $cAbbr ]
Set Field [ reference::conferenceIntroWords; $conIntro ]
Set Field [ reference::conferenceTitle; $conTitle ]
Set Field [ reference::conferenceSubTitle; $conSubTitle ]
Set Field [ reference::conferenceGroupName; $conGname ]
Set Field [ reference::conferenceLocation; $conLocation ]
Set Field [ reference::conferenceDate; $conDate ]
#
Set Field [ reference::korgan; $$organ ]
Set Field [ reference::volumeNumber; $volumeNumber ]
Set Field [ reference::issueNumber; $issueNumber ]
Set Field [ reference::pageNumberRange; $pageNumberRange ]
#
Set Field [ reference::pageNumberOther; $noPP ]
#
Set Field [ reference::kcopyrightHolder; $copyrightHolder ]
Set Field [ reference::TimeRange; $TimeRange ]
#
Set Field [ reference::kcopyist; $$copyist ]
#
Set Field [ reference::publisherTypeAlternative; $notPub ]
Set Field [ reference::publisherTypeOther; $notPubOther ]
Set Field [ reference::publisherLocation; $pubLocation ]
#
Set Field [ reference::pubYear; $pubYear ]
#
Set Field [ reference::PubDate; $pubDate ]
Set Field [ reference::pubDateOther; $pubDateOther ]
#
Set Field [ reference::kHealth; $$health ]
Set Field [ reference::CopyrightYear; $copyrightYear ]
#
Set Field [ reference::copyrightOtherHolder; $copyrightOtherHolder ]
#
Set Field [ reference::URL; $URL ]
Set Field [ reference::URLdate; $URLdate ]
#
Set Field [ reference::library only; $library ]
Set Field [ reference::ISBN; $isbn ]
Set Field [ reference::URLdoi; $doi ]
Set Field [ reference::ISSN; $issn ]
#
Set Field [ reference::ﬁleName; $ﬁleName ]
Set Field [ reference::kﬁleLocation; $InFolder ]
Set Field [ reference::kfolderpath; $$Path ]
Set Field [ reference::kcitation; $citation ]
Set Field [ reference::thoughtsNotesEtc; $notes ]
Set Field [ reference::referenceDump; $refDump ]
#
Set Field [ reference::rights; $rights ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::ktest; TEMP::ktest ]
Set Field [ reference::incomplete; "incomplete" & ¶ ]
#
Set Field [ reference::kcopyrightType; $$copyrightType ]
Set Field [ reference::lock; $$Ref ]
If [ Get ( LayoutName ) = "Reference" ]
Set Field [ reference::ﬁlterFind; "main" & ¶ ]
Set Variable [ $$stoploadCitation ]
#
#Note that citation is for either the node or keyword depending on the citation match.
Else If [ Right ( Get ( LayoutName ) ; 3 ) = "TAG" ]
Set Field [ reference::ﬁlterFind; $$addToTag & ¶ ]
End If
Sort Records [ ]
[ No dialog ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
Go to Layout [ “ReferenceEDIT” (reference) ]
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
January 7, 平成26 17:40:56 Imagination Quality Management.fp7 - duplicateReferenceRecord -2-
