# coding=utf8
# the above tag defines encoding for this document and is for Python 2.x compatibility

import re

regex = r"\/\*(.+)\*\/\n\s*(\S+) \(\*([^)]+)\) \(([^)]+)\);"

test_str = ("	/* GetLastError: vcmpErrorNoSuchEntity */\n"
	"	uint8_t (*IsPlayerAdmin) (int32_t playerId);\n"
	"	/* vcmpErrorNoSuchEntity */\n"
	"	vcmpError (*SetPlayerAdmin) (int32_t playerId, uint8_t toggle);\n"
	"	/* vcmpErrorNoSuchEntity, vcmpErrorNullArgument, vcmpErrorBufferTooSmall */\n"
	"	vcmpError (*GetPlayerIP) (int32_t playerId, char* buffer, size_t size);\n"
	"	/* vcmpErrorNoSuchEntity, vcmpErrorNullArgument, vcmpErrorBufferTooSmall */\n"
	"	vcmpError (*GetPlayerUID) (int32_t playerId, char* buffer, size_t size);\n"
	"	/* vcmpErrorNoSuchEntity, vcmpErrorNullArgument, vcmpErrorBufferTooSmall */\n"
	"	vcmpError (*GetPlayerUID2) (int32_t playerId, char* buffer, size_t size);\n"
	"	/* vcmpErrorNoSuchEntity */\n"
	"	vcmpError (*KickPlayer) (int32_t playerId);\n"
	"	/* vcmpErrorNoSuchEntity */\n"
	"	vcmpError (*BanPlayer) (int32_t playerId);\n"
	"	/* success */\n"
	"	void (*BanIP) (char* ipAddress);\n"
	"	/* success */\n"
	"	uint8_t (*UnbanIP) (char* ipAddress);\n"
	"	/* success */\n"
	"	uint8_t (*IsIPBanned) (char* ipAddress);")

matches = re.finditer(regex, test_str, re.MULTILINE)

for matchNum, match in enumerate(matches):
    matchNum = matchNum + 1
    
    print ("Match {matchNum} was found at {start}-{end}: {match}".format(matchNum = matchNum, start = match.start(), end = match.end(), match = match.group()))
    
    for groupNum in range(0, len(match.groups())):
        groupNum = groupNum + 1
        
        print ("Group {groupNum} found at {start}-{end}: {group}".format(groupNum = groupNum, start = match.start(groupNum), end = match.end(groupNum), group = match.group(groupNum)))

# Note: for Python 2.7 compatibility, use ur"" to prefix the regex and u"" to prefix the test string and substitution.
