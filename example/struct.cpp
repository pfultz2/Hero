
HERO_STRUCT_FIELDS(
    (name, std::string)
    (age, int)
);

HERO_STRUCT_ASSOC_FIELDS(
    ((primary_key))
    ((max_length(512)))
    (name, std::string)
    (age, int)
);

HERO_STRUCT_ASSOC_FIELDS(
    _(primary_key)
    _(max_length(512))
    (name, std::string)
    (age, int)
);

HERO_STRUCT_ASSOC_FIELDS(
    (name, std::string, primary_key, max_length(512))
    (age, int)
);

HERO_STRUCT_ASSOC_FIELDS(
    ((std::string) name, 
        primary_key, 
        max_length(512))
    ((int) age)
);

HERO_STRUCT_ASSOC_FIELDS(
    ((primary_key)(max_length(512))(std::string) name)
    ((int) age)
);

struct person
{
    struct keys
    {
        struct name
        {
            auto attributes()
            {
                return make_attr_map(
                    field_name("name"),
                    primary_key,
                    max_length(512)
                );
            }
        };

        struct age
        {
            auto attributes()
            {
                return make_attr_map(
                    field_name("age")
                );
            }
        };
    };
    struct unpack
    {
        template<class F, class S>
        auto apply(F&& f, S&& s)
        {
            f(
                forward_as_pair(keys::name(), s.name),
                forward_as_pair(keys::age(), s.age)
            );
        }
    };

    std::string name;
    int age;
};

struct person
{
    struct unpack
    {
        template<class F, class S>
        auto apply(F&& f, S&& s)
        {
            f(
                field(s.age, []{ return make_attr_map(field_name("age")); }),
                field(s.name, []
                { 
                    return make_attr_map(
                        field_name("name"),
                        primary_key,
                        max_length(512)
                    ); 
                })
            );
        }
    };

    std::string name;
    int age;
};
