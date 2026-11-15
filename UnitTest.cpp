#include "CppUnitTest.h"
#include "Cinema.h"
#include <limits>
#include <set>
#include <stdexcept>
#include <type_traits>
#include <utility>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace miit::cinema;

static_assert(std::is_abstract_v<Film>);
static_assert(std::is_copy_constructible_v<FeatureFilm>);
static_assert(std::is_copy_assignable_v<AnimatedFilm>);
static_assert(std::is_copy_constructible_v<Cinema>);
static_assert(std::is_copy_assignable_v<Cinema>);
static_assert(std::is_move_constructible_v<Cinema>);
static_assert(std::is_move_assignable_v<Cinema>);

namespace CinemaTests
{
    /**
     * @brief Готовый кинотеатр с двумя залами, тремя фильмами и пятью сеансами на один день
     */
    struct Fixture
    {
        /** @brief Проверяемый кинотеатр */
        Cinema cinema{ "Кинотеатр" };
        /** @brief День, на который созданы сеансы */
        Date today{ 2026, 11, 6 };
        /** @brief ID залов */
        Id hall1 = 0, hall2 = 0;
        /** @brief ID фильмов: приключения 12+, триллер 18+, мультфильм без ограничений */
        Id adventure = 0, thriller = 0, cartoon = 0;
        /** @brief ID сеансов */
        Id s1000 = 0, s1400 = 0, s1800 = 0, s1030 = 0, s1500 = 0;

        /**
         * @brief Наполняет кинотеатр тестовыми данными
         */
        Fixture()
        {
            hall1 = cinema.addHall("Большой", 3).getId();
            hall2 = cinema.addHall("Малый", 2).getId();
            adventure = cinema.addFeatureFilm("Маяк", 110, 12, "Тайна маяка", { "Режиссёр А" },
                { "Актёр А", "Актёр Б" }, "приключения").getId();
            thriller = cinema.addFeatureFilm("Экспресс", 125, 18, "Ночной поезд", { "Режиссёр Б", "Режиссёр В" },
                { "Актёр В" }, "триллер").getId();
            cartoon = cinema.addAnimatedFilm("Лисёнок", 85, 0, "Зимний лес", { "Режиссёр Г" },
                { "Актёр Г" }, "компьютерная").getId();
            s1000 = cinema.addSession(hall1, adventure, today, TimeOfDay(10, 0), 35000).getId();
            s1400 = cinema.addSession(hall1, adventure, today, TimeOfDay(14, 0), 40000).getId();
            s1800 = cinema.addSession(hall1, thriller, today, TimeOfDay(18, 0), 50000).getId();
            s1030 = cinema.addSession(hall2, cartoon, today, TimeOfDay(10, 30), 25000).getId();
            s1500 = cinema.addSession(hall2, adventure, today, TimeOfDay(15, 0), 40000).getId();
        }
    };
}

namespace CinemaTests
{
    /** @brief Проверки календарных дат */
    TEST_CLASS(DateTests)
    {
    public:
        /** @brief Проверяет високосный год, формат и разбор строки */
        TEST_METHOD(LeapYearAndParsing)
        {
            Assert::AreEqual(std::string("2024-02-29"), Date(2024, 2, 29).toString());
            Assert::IsTrue(Date("2026-11-06") == Date(2026, 11, 6));
            Assert::ExpectException<std::invalid_argument>([] { Date d(2025, 2, 29); });
            Assert::ExpectException<std::invalid_argument>([] { Date d("2026-11-6"); });
        }
        /** @brief Проверяет сравнение дат */
        TEST_METHOD(Comparison)
        {
            Assert::IsTrue(Date(2025, 12, 31) < Date(2026, 1, 1));
            Assert::IsTrue(Date(2026, 1, 1) <= Date(2026, 1, 1));
            Assert::IsFalse(Date(2026, 1, 2) < Date(2026, 1, 1));
        }
    };

    /** @brief Проверки времени суток */
    TEST_CLASS(TimeOfDayTests)
    {
    public:
        /** @brief Проверяет формат и разбор строки */
        TEST_METHOD(FormattingAndParsing)
        {
            Assert::AreEqual(std::string("09:05"), TimeOfDay(9, 5).toString());
            Assert::IsTrue(TimeOfDay("18:30") == TimeOfDay(18, 30));
            Assert::AreEqual<int>(1110, TimeOfDay(18, 30).toMinutes());
            Assert::ExpectException<std::invalid_argument>([] { TimeOfDay t(24, 0); });
            Assert::ExpectException<std::invalid_argument>([] { TimeOfDay t(10, 60); });
            Assert::ExpectException<std::invalid_argument>([] { TimeOfDay t("9:30"); });
            Assert::ExpectException<std::invalid_argument>([] { TimeOfDay t("ab:cd"); });
        }
        /** @brief Проверяет сдвиг времени и выход за границы суток */
        TEST_METHOD(AddMinutes)
        {
            Assert::IsTrue(TimeOfDay(10, 0).addMinutes(110) == TimeOfDay(11, 50));
            Assert::IsTrue(TimeOfDay(23, 0).addMinutes(59) == TimeOfDay(23, 59));
            Assert::ExpectException<std::invalid_argument>([] { TimeOfDay(23, 0).addMinutes(60); });
            Assert::ExpectException<std::invalid_argument>([] { TimeOfDay(0, 10).addMinutes(-11); });
        }
        /** @brief Проверяет сравнение времени */
        TEST_METHOD(Comparison)
        {
            Assert::IsTrue(TimeOfDay(9, 59) < TimeOfDay(10, 0));
            Assert::IsTrue(TimeOfDay(10, 0) <= TimeOfDay(10, 0));
            Assert::IsFalse(TimeOfDay(10, 1) < TimeOfDay(10, 0));
        }
    };

    /** @brief Проверки отдельных классов модели */
    TEST_CLASS(ModelTests)
    {
    public:
        /** @brief Проверяет разные положительные ID записей различных типов */
        TEST_METHOD(IdsArePositiveAndUniqueAcrossTypes)
        {
            Hall hall("Зал", 10);
            FeatureFilm feature("Фильм", 90, 0, "Сюжет", { "Р" }, { "А" }, "драма");
            AnimatedFilm animated("Мульт", 80, 0, "Сюжет", { "Р" }, { "А" }, "рисованная");
            Session session(hall.getId(), feature.getId(), Date(2026, 1, 1), TimeOfDay(10, 0), 90, 100);
            Ticket ticket(session.getId(), 1, 100);
            std::set<Id> ids = { hall.getId(), feature.getId(), animated.getId(), session.getId(), ticket.getId() };
            Assert::IsTrue(ids.size() == 5 && ids.count(0) == 0);
        }
        /** @brief Отклоняет пустые названия и числа мест */
        TEST_METHOD(HallAndCinemaValidation)
        {
            Assert::ExpectException<std::invalid_argument>([] { Hall h("  ", 10); });
            Assert::ExpectException<std::invalid_argument>([] { Hall h("Зал", 0); });
            Assert::ExpectException<std::invalid_argument>([] { Cinema c(" \t"); });
        }
        /** @brief Проверяет ограничения данных фильма */
        TEST_METHOD(FilmValidation)
        {
            Assert::ExpectException<std::invalid_argument>([] { FeatureFilm f("", 90, 0, "С", { "Р" }, { "А" }, "г"); });
            Assert::ExpectException<std::invalid_argument>([] { FeatureFilm f("Ф", 0, 0, "С", { "Р" }, { "А" }, "г"); });
            Assert::ExpectException<std::invalid_argument>([] { FeatureFilm f("Ф", 1440, 0, "С", { "Р" }, { "А" }, "г"); });
            Assert::ExpectException<std::invalid_argument>([] { FeatureFilm f("Ф", 90, -1, "С", { "Р" }, { "А" }, "г"); });
            Assert::ExpectException<std::invalid_argument>([] { FeatureFilm f("Ф", 90, 22, "С", { "Р" }, { "А" }, "г"); });
            Assert::ExpectException<std::invalid_argument>([] { FeatureFilm f("Ф", 90, 0, " ", { "Р" }, { "А" }, "г"); });
            Assert::ExpectException<std::invalid_argument>([] { FeatureFilm f("Ф", 90, 0, "С", {}, { "А" }, "г"); });
            Assert::ExpectException<std::invalid_argument>([] { FeatureFilm f("Ф", 90, 0, "С", { "Р" }, { " " }, "г"); });
            Assert::ExpectException<std::invalid_argument>([] { AnimatedFilm f("Ф", 90, 0, "С", { "Р" }, { "А" }, ""); });
        }
        /** @brief Проверяет текст возрастного ограничения */
        TEST_METHOD(AgeRestrictionText)
        {
            FeatureFilm adult("Ф", 90, 18, "С", { "Р" }, { "А" }, "г");
            FeatureFilm free("Ф", 90, 0, "С", { "Р" }, { "А" }, "г");
            Assert::IsTrue(adult.hasAgeRestriction());
            Assert::AreEqual(std::string("18+"), adult.getAgeRestrictionText());
            Assert::IsFalse(free.hasAgeRestriction());
            Assert::AreEqual(std::string("без ограничений"), free.getAgeRestrictionText());
        }
        /** @brief Проверяет копейки в строке и обнаружение переполнения */
        TEST_METHOD(MoneyFormattingAndOverflow)
        {
            Assert::AreEqual(std::string("0.05 руб."), formatMoney(5));
            Assert::AreEqual(std::string("350.00 руб."), formatMoney(35000));
            const Money max = (std::numeric_limits<Money>::max)();
            Assert::ExpectException<std::overflow_error>([=] { checkedAdd(max, 1); });
            Assert::ExpectException<std::invalid_argument>([] { formatMoney(-1); });
        }
        /** @brief Проверяет данные сеанса и билета */
        TEST_METHOD(SessionAndTicketValidation)
        {
            const Date d(2026, 1, 1);
            Assert::ExpectException<std::invalid_argument>([=] { Session s(0, 1, d, TimeOfDay(10, 0), 90, 100); });
            Assert::ExpectException<std::invalid_argument>([=] { Session s(1, 1, d, TimeOfDay(10, 0), 0, 100); });
            Assert::ExpectException<std::invalid_argument>([=] { Session s(1, 1, d, TimeOfDay(10, 0), 90, 0); });
            Assert::ExpectException<std::invalid_argument>([=] { Session s(1, 1, d, TimeOfDay(23, 0), 90, 100); });
            Assert::ExpectException<std::invalid_argument>([] { Ticket t(0, 1, 100); });
            Assert::ExpectException<std::invalid_argument>([] { Ticket t(1, 0, 100); });
            Assert::ExpectException<std::invalid_argument>([] { Ticket t(1, 1, 0); });
        }
        /** @brief Проверяет границы интервала показа и пересечение сеансов */
        TEST_METHOD(SessionRunningAndOverlap)
        {
            const Date d(2026, 1, 1);
            Session a(1, 1, d, TimeOfDay(10, 0), 60, 100);
            Session b(1, 2, d, TimeOfDay(11, 0), 60, 100);
            Session c(1, 2, d, TimeOfDay(10, 30), 60, 100);
            Assert::IsTrue(a.isRunningAt(d, TimeOfDay(10, 0)));
            Assert::IsFalse(a.isRunningAt(d, TimeOfDay(11, 0)));
            Assert::IsFalse(a.isRunningAt(Date(2026, 1, 2), TimeOfDay(10, 30)));
            Assert::IsFalse(a.overlaps(b));
            Assert::IsTrue(a.overlaps(c));
        }
        /** @brief Проверяет итог продаж и программу зала */
        TEST_METHOD(ReportValueObjects)
        {
            Assert::AreEqual<Money>(700, SessionSales(1, 2, 700).getRevenue());
            Assert::ExpectException<std::invalid_argument>([] { SessionSales s(0, 0, 0); });
            Assert::ExpectException<std::invalid_argument>([] { SessionSales s(1, -1, 0); });
            Assert::ExpectException<std::invalid_argument>([] { HallProgram p(1, { 0 }); });
            Assert::AreEqual<std::size_t>(2, HallProgram(1, { 5, 6 }).getFilmIds().size());
        }
    };

    /** @brief Проверки работы кинотеатра и отчётов */
    TEST_CLASS(CinemaServiceTests)
    {
    public:
        /** @brief Показывает сеансы на момент времени с учётом границ */
        TEST_METHOD(SessionsAtGivenTime)
        {
            Fixture f;
            auto atStart = f.cinema.getSessionsAt(f.today, TimeOfDay(10, 0));
            Assert::AreEqual<std::size_t>(1, atStart.size());
            Assert::AreEqual<Id>(f.s1000, atStart[0].get().getId());
            auto both = f.cinema.getSessionsAt(f.today, TimeOfDay(10, 45));
            Assert::AreEqual<std::size_t>(2, both.size());
            Assert::AreEqual<Id>(f.s1000, both[0].get().getId());
            Assert::AreEqual<Id>(f.s1030, both[1].get().getId());
            Assert::AreEqual<std::size_t>(1, f.cinema.getSessionsAt(f.today, TimeOfDay(11, 50)).size());
            Assert::AreEqual<std::size_t>(0, f.cinema.getSessionsAt(f.today, TimeOfDay(11, 55)).size());
            Assert::AreEqual<std::size_t>(0, f.cinema.getSessionsAt(Date(2026, 11, 7), TimeOfDay(10, 45)).size());
        }
        /** @brief Сообщает о возрастном ограничении фильма показанного сеанса */
        TEST_METHOD(AgeRestrictionIsReportedForSessions)
        {
            Fixture f;
            const Film& restricted = f.cinema.getFilm(f.cinema.getSession(f.s1800).getFilmId());
            const Film& free = f.cinema.getFilm(f.cinema.getSession(f.s1030).getFilmId());
            Assert::IsTrue(restricted.hasAgeRestriction());
            Assert::AreEqual(std::string("18+"), restricted.getAgeRestrictionText());
            Assert::IsFalse(free.hasAgeRestriction());
        }
        /** @brief Показывает фильмы по залам без повторов и только за указанный день */
        TEST_METHOD(FilmsByHallsForToday)
        {
            Fixture f;
            auto programs = f.cinema.getFilmsByHalls(f.today);
            Assert::AreEqual<std::size_t>(2, programs.size());
            Assert::AreEqual<Id>(f.hall1, programs[0].getHallId());
            Assert::AreEqual<std::size_t>(2, programs[0].getFilmIds().size());
            Assert::AreEqual<Id>(f.adventure, programs[0].getFilmIds()[0]);
            Assert::AreEqual<Id>(f.thriller, programs[0].getFilmIds()[1]);
            Assert::AreEqual<Id>(f.cartoon, programs[1].getFilmIds()[0]);
            Assert::AreEqual<std::size_t>(0, f.cinema.getFilmsByHalls(Date(2026, 11, 7)).size());
        }
        /** @brief Возвращает цену билета только для пары «сеанс — его фильм» */
        TEST_METHOD(TicketPrice)
        {
            Fixture f;
            Assert::AreEqual<Money>(35000, f.cinema.getTicketPrice(f.s1000, f.adventure));
            Assert::AreEqual<Money>(40000, f.cinema.getTicketPrice(f.s1400, f.adventure));
            Assert::ExpectException<std::invalid_argument>([&] { f.cinema.getTicketPrice(f.s1000, f.thriller); });
            Assert::ExpectException<std::out_of_range>([&] { f.cinema.getTicketPrice(9999, f.adventure); });
            Assert::ExpectException<std::out_of_range>([&] { f.cinema.getTicketPrice(f.s1000, 9999); });
        }
        /** @brief Выдаёт содержание, режиссёров и актёров фильма */
        TEST_METHOD(FilmInfo)
        {
            Fixture f;
            const std::string info = f.cinema.getFilmInfo(f.thriller);
            Assert::IsTrue(info.find("Ночной поезд") != std::string::npos);
            Assert::IsTrue(info.find("Режиссёр Б, Режиссёр В") != std::string::npos);
            Assert::IsTrue(info.find("Актёр В") != std::string::npos);
            Assert::ExpectException<std::out_of_range>([&] { f.cinema.getFilmInfo(9999); });
        }
        /** @brief Продаёт билеты с последовательными местами и учитывает выручку */
        TEST_METHOD(TicketSales)
        {
            Fixture f;
            Assert::AreEqual<Quantity>(3, f.cinema.getFreeSeats(f.s1000));
            const Ticket& first = f.cinema.sellTicket(f.s1000, f.adventure, 30);
            Assert::AreEqual<Quantity>(1, first.getSeat());
            Assert::AreEqual<Money>(35000, first.getPrice());
            Assert::AreEqual<Quantity>(2, f.cinema.sellTicket(f.s1000, f.adventure, 12).getSeat());
            Assert::AreEqual<Quantity>(1, f.cinema.getFreeSeats(f.s1000));
            const SessionSales sales = f.cinema.getSessionSales(f.s1000);
            Assert::AreEqual<Quantity>(2, sales.getTicketsSold());
            Assert::AreEqual<Money>(70000, sales.getRevenue());
        }
        /** @brief Не продаёт билет зрителю младше возрастного ограничения */
        TEST_METHOD(AgeRestrictionBlocksSale)
        {
            Fixture f;
            Assert::ExpectException<std::invalid_argument>([&] { f.cinema.sellTicket(f.s1800, f.thriller, 17); });
            Assert::AreEqual<Quantity>(0, f.cinema.getSessionSales(f.s1800).getTicketsSold());
            Assert::AreEqual<Quantity>(3, f.cinema.getFreeSeats(f.s1800));
            Assert::AreEqual<Quantity>(1, f.cinema.sellTicket(f.s1800, f.thriller, 18).getSeat());
            Assert::ExpectException<std::invalid_argument>([&] { f.cinema.sellTicket(f.s1800, f.thriller, -1); });
            Assert::ExpectException<std::invalid_argument>([&] { f.cinema.sellTicket(f.s1800, f.thriller, 200); });
        }
        /** @brief Не продаёт билет на неподходящий фильм, неизвестный сеанс или при отсутствии мест */
        TEST_METHOD(SaleFailures)
        {
            Fixture f;
            Assert::ExpectException<std::invalid_argument>([&] { f.cinema.sellTicket(f.s1000, f.thriller, 30); });
            Assert::ExpectException<std::out_of_range>([&] { f.cinema.sellTicket(9999, f.adventure, 30); });
            f.cinema.sellTicket(f.s1030, f.cartoon, 5);
            f.cinema.sellTicket(f.s1030, f.cartoon, 6);
            Assert::AreEqual<Quantity>(0, f.cinema.getFreeSeats(f.s1030));
            Assert::ExpectException<std::runtime_error>([&] { f.cinema.sellTicket(f.s1030, f.cartoon, 7); });
            Assert::AreEqual<Quantity>(2, f.cinema.getSessionSales(f.s1030).getTicketsSold());
        }
        /** @brief Показывает продажи по всем сеансам в порядке их добавления */
        TEST_METHOD(SalesBySessions)
        {
            Fixture f;
            f.cinema.sellTicket(f.s1400, f.adventure, 20);
            f.cinema.sellTicket(f.s1800, f.thriller, 40);
            f.cinema.sellTicket(f.s1800, f.thriller, 41);
            auto sales = f.cinema.getSalesBySessions();
            Assert::AreEqual<std::size_t>(5, sales.size());
            Assert::AreEqual<Id>(f.s1000, sales[0].getSessionId());
            Assert::AreEqual<Quantity>(0, sales[0].getTicketsSold());
            Assert::AreEqual<Quantity>(1, sales[1].getTicketsSold());
            Assert::AreEqual<Money>(100000, sales[2].getRevenue());
        }
        /** @brief Отклоняет пересечение сеансов зала, но допускает сеанс встык */
        TEST_METHOD(SessionOverlapRules)
        {
            Fixture f;
            Assert::ExpectException<std::invalid_argument>([&]
                { f.cinema.addSession(f.hall1, f.cartoon, f.today, TimeOfDay(11, 0), 100); });
            Assert::IsTrue(f.cinema.addSession(f.hall1, f.cartoon, f.today, TimeOfDay(11, 50), 100).getEnd() == TimeOfDay(13, 15));
            Assert::IsTrue(f.cinema.addSession(f.hall1, f.cartoon, Date(2026, 11, 7), TimeOfDay(11, 0), 100).getId() != 0);
        }
        /** @brief Проверяет данные нового сеанса и фильма на уровне кинотеатра */
        TEST_METHOD(AddValidation)
        {
            Fixture f;
            Assert::ExpectException<std::out_of_range>([&] { f.cinema.addSession(9999, f.adventure, f.today, TimeOfDay(20, 0), 100); });
            Assert::ExpectException<std::out_of_range>([&] { f.cinema.addSession(f.hall1, 9999, f.today, TimeOfDay(20, 0), 100); });
            Assert::ExpectException<std::invalid_argument>([&] { f.cinema.addSession(f.hall1, f.adventure, f.today, TimeOfDay(20, 0), 0); });
            Assert::ExpectException<std::invalid_argument>([&] { f.cinema.addSession(f.hall1, f.thriller, f.today, TimeOfDay(23, 0), 100); });
            Assert::ExpectException<std::invalid_argument>([&]
                { f.cinema.addAnimatedFilm(" Маяк ", 80, 0, "С", { "Р" }, { "А" }, "рисованная"); });
        }
        /** @brief Хранит фильмы разных видов в одной коллекции базового типа */
        TEST_METHOD(PolymorphicFilmCollection)
        {
            Fixture f;
            auto films = f.cinema.getFilms();
            Assert::AreEqual<std::size_t>(3, films.size());
            const Film& first = films[0];
            const Film& last = films[2];
            Assert::IsTrue(dynamic_cast<const FeatureFilm*>(&first) != nullptr);
            Assert::IsTrue(dynamic_cast<const AnimatedFilm*>(&last) != nullptr);
            Assert::AreEqual(std::string("Мультфильм"), last.getKind());
            Assert::IsTrue(films[0].get().getId() < films[1].get().getId());
        }
        /** @brief Копия кинотеатра независима и сохраняет ID записей */
        TEST_METHOD(CopyIsIndependent)
        {
            Fixture f;
            f.cinema.sellTicket(f.s1000, f.adventure, 30);
            Cinema copy = f.cinema;
            copy.sellTicket(f.s1000, f.adventure, 30);
            Assert::AreEqual<Quantity>(1, f.cinema.getSessionSales(f.s1000).getTicketsSold());
            Assert::AreEqual<Quantity>(2, copy.getSessionSales(f.s1000).getTicketsSold());
            Assert::AreEqual<Id>(f.adventure, copy.getFilm(f.adventure).getId());
        }
    };
}
