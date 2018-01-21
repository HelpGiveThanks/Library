January 21, 2018 11:13:42 Library.fmp12 - CHUNK_insertPageNumbersForwardOnePage -1-
test: report: print: CHUNK_insertPageNumbersForwardOnePage
Select Window [ Name: "Report"; Current file ]
Go to Record/Request/Page
[ Next ]
Set Variable [ $page; Value:Get ( PageNumber ) ]
Set Field [ TEMP::pageNumber; $page ]
Select Window [ Name: "Numbers"; Current file ]
