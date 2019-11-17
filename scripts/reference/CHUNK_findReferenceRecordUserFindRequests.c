November 13, 2019 13:04:41 Library.fmp12 - -1-
CHUNK_findReferenceRecordUserFindRequests
reference: CHUNK_findReferenceRecordUserFindRequests
#
#
#Capture the user's current find requests.
If [ $$captureUserFindRequests = 1 ]
// Set Variable [ $$r0; Value:reference::createDate ]
// Set Variable [ $$r1; Value:reference::modifyDate ]
Set Variable [ $$r2; Value:reference::showInLearn ]
Set Variable [ $$r3; Value:reference::incomplete ]
Set Variable [ $$r4; Value:reference::referenceForReferenceFINDWindow ]
Set Variable [ $$r5; Value:reference::kisON ]
Set Variable [ $$r5b; Value:reference::showMedia ]
Set Variable [ $$r5c; Value:reference::showMedia[2] ]
Set Variable [ $$r6; Value:reference::kisWhat ]
Set Variable [ $$r7; Value:reference::otherIsOn ]
Set Variable [ $$r8; Value:reference::referenceNodes ]
Set Variable [ $$r9; Value:reference::Title ]
Set Variable [ $$r10; Value:reference::bookChapter ]
Set Variable [ $$r11; Value:reference::governmentAuthor ]
Set Variable [ $$r12; Value:reference::GovernmentDocInfo ]
Set Variable [ $$r13; Value:reference::letterDate ]
Set Variable [ $$r14; Value:reference::emailRecipient ]
Set Variable [ $$r15; Value:reference::publicationTitle ]
Set Variable [ $$r16; Value:reference::compilationEditors ]
Set Variable [ $$r17a; Value:reference::compilationAbbr ]
Set Variable [ $$r17b; Value:reference::compilationNumberOfEditors ]
Set Variable [ $$r18; Value:reference::conferenceIntroWords ]
Set Variable [ $$r19; Value:reference::conferenceTitle ]
Set Variable [ $$r20; Value:reference::conferenceSubTitle ]
Set Variable [ $$r22; Value:reference::conferenceLocation ]
Set Variable [ $$r23; Value:reference::conferenceDate ]
Set Variable [ $$r24; Value:reference::volumeNumber ]
Set Variable [ $$r25; Value:reference::issueNumber ]
Set Variable [ $$r26; Value:reference::pageNumberRange ]
Set Variable [ $$r26b; Value:reference::pageNumberOther ]
Set Variable [ $$r27; Value:reference::TimeRange ]
Set Variable [ $$r28; Value:reference::publisherTypeAlternative ]
Set Variable [ $$r29; Value:reference::publisherLocation ]
Set Variable [ $$r30; Value:reference::publicationYearOrStuffOrderNumber ]
Set Variable [ $$r31; Value:reference::PubDate ]
Set Variable [ $$r32; Value:reference::pubDateOther ]
Set Variable [ $$r33; Value:reference::CopyrightYear ]
Set Variable [ $$r34; Value:reference::copyrightOtherHolder ]
Set Variable [ $$r35; Value:reference::URL ]
Set Variable [ $$r36; Value:reference::URLdate ]
Set Variable [ $$r37; Value:reference::publicLibraryLinks ]
Set Variable [ $$r38; Value:reference::ISBN ]
Set Variable [ $$r39; Value:reference::DOI ]
Set Variable [ $$r40; Value:reference::ISSN ]
Set Variable [ $$r41; Value:reference::fileName ]
Set Variable [ $$r42; Value:reference::kfileLocation ]
Set Variable [ $$r43; Value:reference::thoughtsNotesEtc ]
Set Variable [ $$r44; Value:reference::referenceDump ]
End If
#
#
#Put back the user's current find requests.
If [ $$putBackUserFindRequests = 1 ]
// Set Field [ reference::createDate; $$r0 ]
// Set Field [ reference::modifyDate; $$r1 ]
Set Field [ reference::showInLearn; $$r2 ]
Set Field [ reference::incomplete; $$r3 ]
Set Field [ reference::referenceForReferenceFINDWindow; $$r4 ]
Set Field [ reference::kisON; $$r5 ]
Set Field [ reference::showMedia; $$r5b ]
Set Field [ reference::showMedia[2]; $$r5c ]
Set Field [ reference::kisWhat; $$r6 ]
Set Field [ reference::otherIsOn; $$r7 ]
Set Field [ reference::referenceNodes; $$r8 ]
Set Field [ reference::Title; $$r9 ]
Set Field [ reference::bookChapter; $$r10 ]
Set Field [ reference::governmentAuthor; $$r11 ]
Set Field [ reference::GovernmentDocInfo; $$r12 ]
Set Field [ reference::letterDate; $$r13 ]
Set Field [ reference::emailRecipient; $$r14 ]
Set Field [ reference::publicationTitle; $$r15 ]
Set Field [ reference::compilationEditors; $$r16 ]
Set Field [ reference::compilationAbbr; $$r17a ]
Set Field [ reference::compilationNumberOfEditors; $$r17b ]
Set Field [ reference::conferenceIntroWords; $$r18 ]
Set Field [ reference::conferenceTitle; $$r19 ]
Set Field [ reference::conferenceSubTitle; $$r20 ]
Set Field [ reference::conferenceLocation; $$r22 ]
Set Field [ reference::conferenceDate; $$r23 ]
Set Field [ reference::volumeNumber; $$r24 ]
Set Field [ reference::issueNumber; $$r25 ]
Set Field [ reference::pageNumberRange; $$r26 ]
Set Field [ reference::pageNumberOther; $$r26b ]
Set Field [ reference::TimeRange; $$r27 ]
Set Field [ reference::publisherTypeAlternative; $$r28 ]
Set Field [ reference::publisherLocation; $$r29 ]
Set Field [ reference::publicationYearOrStuffOrderNumber; $$r30 ]
Set Field [ reference::PubDate; $$r31 ]
Set Field [ reference::pubDateOther; $$r32 ]
Set Field [ reference::CopyrightYear; $$r33 ]
Set Field [ reference::copyrightOtherHolder; $$r34 ]
Set Field [ reference::URL; $$r35 ]
Set Field [ reference::URLdate; $$r36 ]
Set Field [ reference::publicLibraryLinks; $$r37 ]
Set Field [ reference::ISBN; $$r38 ]
Set Field [ reference::DOI; $$r39 ]
Set Field [ reference::ISSN; $$r40 ]
Set Field [ reference::fileName; $$r41 ]
Set Field [ reference::kfileLocation; $$r42 ]
Set Field [ reference::thoughtsNotesEtc; $$r43 ]
Set Field [ reference::referenceDump; $$r44 ]
End If
#
#
#Clear the user's current find requests.
If [ $$clearUserFindRequests = 1 ]
Set Variable [ $$r0 ]
Set Variable [ $$r1 ]
Set Variable [ $$r2 ]
Set Variable [ $$r3 ]
Set Variable [ $$r4 ]
Set Variable [ $$r5 ]
Set Variable [ $$r5b ]
Set Variable [ $$r5c ]
Set Variable [ $$r6 ]
Set Variable [ $$r7 ]
Set Variable [ $$r8 ]
Set Variable [ $$r9 ]
Set Variable [ $$r10 ]
Set Variable [ $$r11 ]
Set Variable [ $$r12 ]
Set Variable [ $$r13 ]
Set Variable [ $$r14 ]
Set Variable [ $$r15 ]
Set Variable [ $$r16 ]
Set Variable [ $$r17a ]
Set Variable [ $$r17b ]
Set Variable [ $$r18 ]
Set Variable [ $$r19 ]
Set Variable [ $$r20 ]
Set Variable [ $$r21 ]
Set Variable [ $$r22 ]
Set Variable [ $$r23 ]
Set Variable [ $$r24 ]
Set Variable [ $$r25 ]
Set Variable [ $$r26 ]
Set Variable [ $$r26b ]
Set Variable [ $$r27 ]
Set Variable [ $$r28 ]
Set Variable [ $$r29 ]
Set Variable [ $$r30 ]
Set Variable [ $$r31 ]
Set Variable [ $$r32 ]
Set Variable [ $$r33 ]
Set Variable [ $$r34 ]
Set Variable [ $$r35 ]
Set Variable [ $$r36 ]
Set Variable [ $$r37 ]
Set Variable [ $$r38 ]
Set Variable [ $$r39 ]
Set Variable [ $$r40 ]
Set Variable [ $$r41 ]
Set Variable [ $$r42 ]
Set Variable [ $$r43 ]
Set Variable [ $$r44 ]
End If
#
#
