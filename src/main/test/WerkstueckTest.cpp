#include "../Logic/Werkstueck.h"


class WerkstueckTest {
public:
    void testFromJson() {
        // Test valid json string
        string json = "{\"werkstueckTyp\":1,\"absoluteHoehe\":2,\"mittlereHoehe\":3,\"wkFlipped\":true,\"aussortieren\":false}";
        Werkstueck wk = Werkstueck(json);
        if (wk.werkstueckTyp != 1 || wk.absoluteHoehe != 2 || wk.mittlereHoehe != 3 || !wk.wkFlipped || wk.aussortieren) {
            cout << "Error: testFromJson() with valid json string" << endl;
        }

        // Test invalid json string
        json = "{\"werkstueckTyp\":1,\"absoluteHoehe\":\"invalid\",\"mittlereHoehe\":3,\"wkFlipped\":true,\"aussortieren\":false}";
        try {
            Werkstueck wk2 = Werkstueck(json);
            cout << "Error: testFromJson() with invalid json string" << endl;
        } catch (...) {
            // exception is expected
        }
    }

    void testToJson() {
        Werkstueck wk;
        wk.werkstueckTyp = 1;
        wk.absoluteHoehe = 2;
        wk.mittlereHoehe = 3;
        wk.wkFlipped = true;
        wk.aussortieren = false;

        string json = wk.toJsonString();
        if (json != "{\"werkstueckTyp\":1,\"absoluteHoehe\":2,\"mittlereHoehe\":3,\"wkFlipped\":true,\"aussortieren\":false}") {
            cout << "Error: testToJson()" << endl;
}
    }
};
