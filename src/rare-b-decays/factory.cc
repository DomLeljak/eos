/* vim: set sw=4 sts=4 et foldmethod=syntax : */

#include <src/rare-b-decays/factory.hh>
#include <src/rare-b-decays/exclusive-b-to-s-dilepton.cc>
#include <src/rare-b-decays/inclusive-b-to-s-dilepton.cc>

namespace wf
{
    ObservablePtr
    RareBFactory::make(const std::string & name, const Parameters & parameters, const ObservableOptions & options)
    {
        static const std::map<std::string, ObservableFactory *> simple_observables
        {
#ifdef OBSERVABLE0
# undef OBSERVABLE0
#endif
#ifdef OBSERVABLE1
# undef OBSERVABLE1
#endif
#ifdef OBSERVABLE2
# undef OBSERVABLE2
#endif

#define OBSERVABLE0(name_, decay_, function_) \
            std::make_pair(name_, new ConcreteObservableFactory<decay_, 0>( \
                        ConcreteObservableData<decay_, 0>(name_, std::tr1::mem_fn(&decay_::function_))))
#define OBSERVABLE1(name_, decay_, function_, var1_) \
            std::make_pair(name_, new ConcreteObservableFactory<decay_, 1>( \
                        ConcreteObservableData<decay_, 1>(name_, std::tr1::mem_fn(&decay_::function_), var1_)))
#define OBSERVABLE2(name_, decay_, function_, var1_, var2_) \
            std::make_pair(name_, new ConcreteObservableFactory<decay_, 2>( \
                        ConcreteObservableData<decay_, 2>(name_, std::tr1::mem_fn(&decay_::function_), var1_, var2_)))

            /* Exclusive Decays */

            // B -> K^* ll, Large Recoil
            OBSERVABLE1("B->K^*ll::dBR/ds@LargeRecoil",   BToKstarDilepton<LargeRecoil>, differential_branching_ratio,            "s"),
            OBSERVABLE1("B->K^*ll::A_FB(s)@LargeRecoil",  BToKstarDilepton<LargeRecoil>, differential_forward_backward_asymmetry, "s"),
            OBSERVABLE1("B->K^*ll::A_T^2(s)@LargeRecoil", BToKstarDilepton<LargeRecoil>, differential_transverse_asymmetry_2,     "s"),
            OBSERVABLE1("B->K^*ll::A_T^3(s)@LargeRecoil", BToKstarDilepton<LargeRecoil>, differential_transverse_asymmetry_3,     "s"),
            OBSERVABLE1("B->K^*ll::A_T^4(s)@LargeRecoil", BToKstarDilepton<LargeRecoil>, differential_transverse_asymmetry_4,     "s"),
            OBSERVABLE1("B->K^*ll::F_L(s)@LargeRecoil",   BToKstarDilepton<LargeRecoil>, differential_longitudinal_polarisation,  "s"),
            OBSERVABLE2("B->K^*ll::A_FB@LargeRecoil",     BToKstarDilepton<LargeRecoil>, integrated_forward_backward_asymmetry,   "s_min", "s_max"),
            OBSERVABLE2("B->K^*ll::BR@LargeRecoil",       BToKstarDilepton<LargeRecoil>, integrated_branching_ratio,              "s_min", "s_max"),

            // B -> K^* ll, Low Recoil
            OBSERVABLE1("B->K^*ll::dBR/ds@LowRecoil",     BToKstarDilepton<LowRecoil>, differential_branching_ratio,            "s"),
            OBSERVABLE1("B->K^*ll::A_FB(s)@LowRecoil",    BToKstarDilepton<LowRecoil>, differential_forward_backward_asymmetry, "s"),
            OBSERVABLE1("B->K^*ll::A_T^2(s)@LowRecoil",   BToKstarDilepton<LowRecoil>, differential_transverse_asymmetry_2,     "s"),
            OBSERVABLE1("B->K^*ll::A_T^3(s)@LowRecoil",   BToKstarDilepton<LowRecoil>, differential_transverse_asymmetry_3,     "s"),
            OBSERVABLE1("B->K^*ll::A_T^4(s)@LowRecoil",   BToKstarDilepton<LowRecoil>, differential_transverse_asymmetry_4,     "s"),
            OBSERVABLE1("B->K^*ll::F_L(s)@LowRecoil",     BToKstarDilepton<LowRecoil>, differential_longitudinal_polarisation,  "s"),
            OBSERVABLE2("B->K^*ll::A_FB@LowRecoil",       BToKstarDilepton<LowRecoil>, integrated_forward_backward_asymmetry,   "s_min", "s_max"),
            OBSERVABLE2("B->K^*ll::BR@LowRecoil",         BToKstarDilepton<LowRecoil>, integrated_branching_ratio,              "s_min", "s_max"),

            /* Inclusive Decays */
            OBSERVABLE1("B->X_sll::dBR/ds@GN1997", BToXsDilepton<GN1997>, differential_branching_ratio, "s"),
            OBSERVABLE2("B->X_sll::BR@GN1997",     BToXsDilepton<GN1997>, integrated_branching_ratio,   "s_min", "s_max"),
        };

        ObservableOptions myoptions(options);
        if (! myoptions.has("form-factors"))
            myoptions.set("form-factors", "BZ2004");

        auto i(simple_observables.find(name));
        if (simple_observables.end() == i)
            return std::tr1::shared_ptr<Observable>();

        return i->second->make(parameters, myoptions);
    }
}
