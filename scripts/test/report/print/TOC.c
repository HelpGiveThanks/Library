testScreens: testReport: print: TOC
Set Variable [ $record; Value:Get (RecordNumber) ]
Set Variable [ $TOCnumber; Value:report::TOCnumbers ]
Set Variable [ $TOC; Value:report::TOC ]
Go to Field [ ]
Go to Record/Request/Page
[ First ]
Loop
Set Field [ report::TOCnumbers; $TOCnumber ]
Set Field [ report::TOC; $TOC ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Go to Record/Request/Page [ $record ]
[ No dialog ]
Go to Field [ ]
January 7, 平成26 14:46:29 Imagination Quality Management.fp7 - TOC -1-
