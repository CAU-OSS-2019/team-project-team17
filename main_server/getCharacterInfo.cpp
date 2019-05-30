#include "db/getCharacterInfo.h"


map<base_character_key, float> GetCharacterInfo::getBaseCharacterInfo() {
			cout << "Get Base Character Information" << endl;

			// Connect
			mysql_init(&conn);

			connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

			if (connection == NULL) {
				cout << "DB Not Connected : " << mysql_error(&conn) << endl;
				return base_character_map;
			}

			// Query
			sprintf(query, "SELECT * FROM baseCharacterInfo");

			query_state = mysql_query(connection, query);

			if (query_state != 0) {
				cout << "getting character information failed : " << mysql_error(&conn) << endl;
				mysql_close(&conn);
				return base_character_map;
			}

			// Result
			sql_result = mysql_store_result(connection);

			base_character_key bc_key;
			float win_rate;

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				//set_base_character_info(sql_row);
				bc_key.character_name = sql_row[0];
				bc_key.rank = sql_row[1];
				win_rate = atof(sql_row[2]);

				base_character_map.insert(pair<base_character_key, float>(bc_key, win_rate));
			}	

			// Close
			mysql_free_result(sql_result);
			mysql_close(&conn);

			return base_character_map;
		}

