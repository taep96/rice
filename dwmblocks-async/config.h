#define CMDLENGTH 500
#define DELIMITER "<"
#define CLICKABLE_BLOCKS

const Block blocks[] = {
	BLOCK("echo 🎵 $(now-playing 2> /dev/null)",                        5,     1),
	BLOCK("echo 📦 $(checkupdates | wc -l) updates",                    60,    2),
	BLOCK("echo 🕑 $(date +\"%a, %B %d %l:%M%p\" | sed 's/  / /g')",    5,     3),
};
