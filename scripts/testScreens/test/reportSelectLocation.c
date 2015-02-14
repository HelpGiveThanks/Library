testScreens: test: ReportSelectLocation
If [ Get ( LayoutName ) = "ReportLocationSelect" ]
#note general or canned location user identified
Set Variable [ $$locationName; Value:testlearnReportTags::gkaudienceLocation ]
Set Field [ TEMP::kuserLocation; $$locationName ]
#
#note new location ID number and name user created for this specific location in the contact's building
Set Variable [ $$location; Value:tagTestSubjectLocation::_LtestSubjectLocation ]
Close Window [ Current Window ]
Exit Script [ ]
End If
If [ testlearnReportTags::kreportNumber ≠ $$reportNumber ]
Show Custom Dialog [ Title: "!"; Message: "This evidence is a favority from another report, so its location information cannot be used for creating location based evidence for this report."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#set up new discovery field name with this
#item's information.
Set Field [ TEMP::LocationName; testlearnReportTags::Location ]
Set Field [ TEMP::kuserLocation; testlearnReportTags::kaudienceLocation ]
Set Field [ testlearnReportTags::gkaudienceLocation; testlearnReportTags::kaudienceLocation ]
Set Field [ TEMP::TimeStamp; testlearnReportTags::timestamp ]
January 7, 平成26 12:50:16 Imagination Quality Management.fp7 - ReportSelectLocation -1-
