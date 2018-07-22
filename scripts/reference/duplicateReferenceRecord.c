July 20, 2018 21:50:57 Library.fmp12 - duplicateReferenceRecord -1-
reference: duplicateReferenceRecord
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode (update)” ]
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Currently in find mode. Click done in the tag menus window to exit find mode, and then click
this button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If in find mode, exit find mode.
If [ $$findMode= 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Go to Layout [ $$findLayout ]
Set Variable [ $$stoploadCitation ]
Select Window [ Name: "References"; Current file ]
End If
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
Select Window [ Name: "References"; Current file ]
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ ]
[ No dialog ]
End If
#
#Capture all record information to be duplicated.
Set Variable [ $type; Value:reference::kisON ]
Set Variable [ $media; Value:reference::kisWhat ]
Set Variable [ $typeOther; Value:reference::otherIsOn ]
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
Set Variable [ $showMedia1; Value:reference::showMedia[1] ]
Set Variable [ $showMedia2; Value:reference::showMedia[2] ]
#
Set Variable [ $chapter; Value:reference::bookChapter ]
Set Variable [ $dissertation; Value:reference::dissertationThesisUniversity ]
Set Variable [ $govt; Value:reference::governmentAuthor ]
Set Variable [ $govtDoc; Value:reference::GovernmentDocInfo ]
Set Variable [ $letter; Value:reference::letterDate ]
Set Variable [ $email; Value:reference::emailRecipient ]
Set Variable [ $ctitle; Value:reference::publicationTitle ]
Set Variable [ $ceditor; Value:reference::compilationEditors ]
Set Variable [ $cnumber; Value:reference::compilationNumberOfEditors ]
Set Variable [ $cAbbr; Value:reference::compilationAbbr ]
Set Variable [ $conIntro; Value:reference::conferenceIntroWords ]
Set Variable [ $conTitle; Value:reference::conferenceTitle ]
Set Variable [ $conSubTitle; Value:reference::conferenceSubTitle ]
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
Set Variable [ $pubYear; Value:reference::publicationYearOrStuffOrderNumber ]
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
Set Variable [ $library; Value:reference::publicLibraryLinks ]
Set Variable [ $isbn; Value:reference::ISBN ]
Set Variable [ $doi; Value:reference::DOI ]
Set Variable [ $issn; Value:reference::ISSN ]
#
Set Variable [ $fileName; Value:reference::fileName ]
Set Variable [ $InFolder; Value:reference::kfileLocation ]
Set Variable [ $citation; Value:reference::kcitation ]
Set Variable [ $notes; Value:reference::thoughtsNotesEtc ]
Set Variable [ $refDump; Value:reference::referenceDump ]
#
Set Variable [ $rights; Value:reference::rights ]
Go to Field [ ]
#
#Now create a new record and give it the
#copied information.
Set Variable [ $$stoploadCitation; Value:1 ]
New Record/Request
#
#
Set Field [ reference::kisON; $type ]
Set Field [ reference::kisWhat; $media ]
Set Field [ reference::otherIsOn; $typeOther ]
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
Set Field [ reference::showMedia; $showMedia1 ]
Set Field [ reference::showMedia[2]; $showMedia2 ]
#
Set Field [ reference::bookChapter; $chapter ]
Set Field [ reference::dissertationThesisUniversity; $dissertation ]
Set Field [ reference::governmentAuthor; $govt ]
Set Field [ reference::GovernmentDocInfo; $govtDoc ]
Set Field [ reference::letterDate; $letter ]
Set Field [ reference::emailRecipient; $email ]
Set Field [ reference::publicationTitle; $ctitle ]
Set Field [ reference::compilationEditors; $ceditor ]
Set Field [ reference::compilationNumberOfEditors; $cnumber ]
Set Field [ reference::compilationAbbr; $cAbbr ]
Set Field [ reference::conferenceIntroWords; $conIntro ]
Set Field [ reference::conferenceTitle; $conTitle ]
Set Field [ reference::conferenceSubTitle; $conSubTitle ]
Set Field [ reference::conferenceLocation; $conLocation ]
Set Field [ reference::conferenceDate; $conDate ]
#
Set Field [ reference::kpublication; $$publication ]
Set Field [ reference::volumeNumber; $volumeNumber ]
Set Field [ reference::issueNumber; $issueNumber ]
Set Field [ reference::pageNumberRange; $pageNumberRange ]
#
Set Field [ reference::pageNumberOther; $noPP ]
#
Set Field [ reference::kcopyrightHolder; $copyrightHolder ]
Set Field [ reference::TimeRange; $TimeRange ]
#
Set Field [ reference::kpublisher; $$publisher ]
#
Set Field [ reference::publisherTypeAlternative; $notPub ]
Set Field [ reference::publisherTypeOther; $notPubOther ]
Set Field [ reference::publisherLocation; $pubLocation ]
#
Set Field [ reference::publicationYearOrStuffOrderNumber; $pubYear ]
#
Set Field [ reference::PubDate; $pubDate ]
Set Field [ reference::pubDateOther; $pubDateOther ]
#
Set Field [ reference::kCopyright; $$copyright ]
Set Field [ reference::CopyrightYear; $copyrightYear ]
#
Set Field [ reference::copyrightOtherHolder; $copyrightOtherHolder ]
#
Set Field [ reference::URL; $URL ]
Set Field [ reference::URLdate; $URLdate ]
#
Set Field [ reference::publicLibraryLinks; $library ]
Set Field [ reference::ISBN; $isbn ]
Set Field [ reference::DOI; $doi ]
Set Field [ reference::ISSN; $issn ]
#
Set Field [ reference::fileName; $fileName ]
Set Field [ reference::kfileLocation; $InFolder ]
Set Field [ reference::kfolderpath; $$Path ]
Set Field [ reference::kcitation; $citation ]
Set Field [ reference::thoughtsNotesEtc; $notes ]
Set Field [ reference::referenceDump; $refDump ]
#
Set Field [ reference::rights; $rights ]
Set Field [ reference::ktest; TEMP::ktestSubsection ]
#
Set Field [ reference::kcopyrightType; $$copyrightType ]
Set Field [ reference::lock; $$Ref ]
#
#
#Load new record as the record being
#focused on.
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadLearnOrRefMainRecord (update)” ]
#
#Determine if in stuff or idea mode.
If [ TEMP::InventoryLibraryYN ≠ "" ]
#
#If in stuff mode than select to
#show record in the Learn section.
Set Field [ reference::showInLearn; "show in learn" ]
#
#Decided to make main reference layout also
#include the fields that will be edited, so no
#need in stuffLibrary mode to go an
#edit layout.
Else
#
#If in idea mode then open new record in a
#separate window. This is neccessary to allow
#user to scroll thru just this new record after
#finding just this new record in the new
#window.
# Also, the new window strategy means the
#main reference window will not need to be
#resorted, and so moved unless the
#alphabetical location of this new record
#requires it to be resorted.
Set Variable [ $$stoploadCitation; Value:1 ]
Sort Records [ ]
[ No dialog ]
Set Variable [ $$editRecord; Value:Get (RecordNumber) ]
Go to Record/Request/Page [ $$editRecord ]
[ No dialog ]
#
#Go to edit layout in new window.
Set Window Title [ Current Window; New Title: "Hidden" ]
#
#Mark record as incomplete.
Set Field [ reference::incomplete; "incomplete" & ¶ ]
#
#For some reason it is essential that a Go to
#field step is included prior to opening the
#new window for Add to tags scripts to work.
Go to Field [ ]
#
New Window [ Name: "References"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
Go to Layout [ “ReferenceEDIT” (reference) ]
#
#Find just the record to be edited.
Enter Find Mode [ ]
Set Field [ reference::_Lreference; $$citationRecord ]
Perform Find [ ]
Set Variable [ $$stoploadCitation ]
#
End If
#
#Prevent add mode.
Set Variable [ $$stopAdd; Value:1 ]
#
#
