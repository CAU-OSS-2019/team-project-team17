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
		strcpy(bc_key.character_name , sql_row[0]);
		strcpy(bc_key.rank , sql_row[1]);
		win_rate = atof(sql_row[2]);
		//cout<<bc_key.character_name<<" "<<bc_key.rank<<" "<<win_rate<<endl;
		base_character_map.insert(pair<base_character_key, float>(bc_key, win_rate));
	}	

	// Close
	mysql_free_result(sql_result);
	mysql_close(&conn);

	return base_character_map;
}

map<best_pick_key, best_pick_value> GetCharacterInfo::getBestPickCharacter() {
	cout << "Get Best Pick Character Information" << endl;

	// Connect
	mysql_init(&conn);
	mysql_options(&conn, MYSQL_SET_CHARSET_NAME, "euckr");		//euckr
	mysql_options(&conn, MYSQL_INIT_COMMAND, "SET NAMES euckr");

	connection = mysql_real_connect(&conn, HOST, USERNAME, PASSWORD, DBNAME, PORTNUM, NULL, 0);

	if (connection == NULL) {
		cout << "DB Not Connected : " << mysql_error(&conn) << endl;
		return best_pick_map;
	}

	// Query
	sprintf(query, "SELECT * FROM bestPickCharacter");

	query_state = mysql_query(connection, query);

	if (query_state != 0) {
		cout << "getting best character information failed : " << mysql_error(&conn) << endl;
		mysql_close(&conn);
		return best_pick_map;
	}

	// Result
	sql_result = mysql_store_result(connection);
	best_pick_key bp_key;
	best_pick_value bp_value;
	int countd=0;
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {

cout<<++countd<<endl;		//set_base_character_info(sql_row);
		strcpy(bp_key.character_name , sql_row[0]);
		strcpy(bp_key.rank , sql_row[1]);
		strcpy(bp_key.best_character , sql_row[2]);
		bp_value.win_rate = atof(sql_row[3]);
		strcpy(bp_value.description , sql_row[4]);
		//cout<<sql_row[0]<<" "<<sql_row[1]<<" "<<sql_row[2]<<" "<<sql_row[3]<<" "<<sql_row[4]<<endl;
		best_pick_map.insert(pair<best_pick_key, best_pick_value>(bp_key, bp_value));
	}

	// Close
	mysql_free_result(sql_result);
	mysql_close(&conn);

	return best_pick_map;
}
