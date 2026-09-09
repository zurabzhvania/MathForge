#ifndef UI_H
#define UI_H

#include <string>

namespace UI
{
    void showMainHeader();

    void showIntegrationHeader();

    void showErrorHeader();

    void showApplicationsHeader();

    void showDerivativeHeader();

    void showLimitsHeader();

    void showSeriesHeader();

    void showDerivativeExplanation();

    void showLimitExplanation();

    void showArcLengthExplanation();

    void showSuccessMessage(
        const std::string& message
    );

    void showErrorMessage(
        const std::string& message
    );
}

#endif
