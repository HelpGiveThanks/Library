startclose: closeLibrary
// Go to Layout [ “startMemorySwitch” (MemorySwitch) ]
// Show All Records
// Go to Record/Request/Page
[ First ]
// Loop
// Exit Loop If [ tempSetup::ﬁlePath ≠ MemorySwitch::path ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// If [ tempSetup::ﬁlePath ≠ MemorySwitch::path ]
// New Record/Request
// Set Field [ MemorySwitch::path; TEMP::ﬁlePath ]
// Set Field [ MemorySwitch::name; TEMP::ﬁleName ]
// End If
Close Window [ Current Window ]
Close Window [ Name: "Tag Menus"; Current ﬁle ]
January 7, 平成26 12:01:44 Imagination Quality Management.fp7 - closeLibrary -1-
